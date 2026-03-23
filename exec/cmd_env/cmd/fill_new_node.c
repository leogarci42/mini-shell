/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:29:33 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/14 18:51:34 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_boolean	ft_is_heredoc(t_cmd *new, char ***heredoc)
{
	int	len;
	int	i;

	new->infile = ft_strdup(*heredoc[0]);
	if (!new->infile)
		return (FALSE);
	free(*heredoc[0]);
	len = ft_splitlen(*heredoc);
	i = 0;
	while (i < len - 1)
	{
		(*heredoc)[i] = (*heredoc)[i + 1];
		i++;
	}
	(*heredoc)[i] = NULL;
	return (TRUE);
}

static t_boolean	ft_is_redir_in(t_cmd *new, t_tokenizer *tmp,
	char ***heredoc)
{
	int	fd;

	if (new->infile)
		free(new->infile);
	if (tmp->role == STATE_REDIR_IN_TARGET)
	{
		fd = open(tmp->value, O_RDONLY);
		if ((fd) == -1)
		{
			new->infile = ft_strdup("");
			perror("open");
		}
		else
		{
			if (close(fd) == -1)
				return (perror("close"), FALSE);
			new->infile = ft_strdup(tmp->value);
		}
	}
	if (tmp->role == STATE_HEREDOC_DOC)
		if (ft_is_heredoc(new, heredoc) == FALSE)
			return (FALSE);
	return (TRUE);
}

static void	ft_append_or_trunc(t_cmd *new, t_tokenizer *tmp)
{
	if (tmp->role == STATE_APPEN)
		new->redir_type = APPEND;
	if (tmp->role == STATE_REDIR_OUT)
		new->redir_type = TRUNC;
}

static t_boolean	ft_is_redir_out(t_cmd *new, t_tokenizer *tmp)
{
	int	fd;

	if (tmp->role == STATE_REDIR_OUT_TARGET
		|| tmp->role == STATE_APPEN_TARGET)
	{
		fd = open(tmp->value, O_CREAT | O_WRONLY, 0644);
		if ((fd) == -1)
		{
			if (new->outfile)
				free(new->outfile);
			new->outfile = ft_strdup(tmp->value);
			if (!new->outfile)
				return (FALSE);
			return (perror("open"), FALSE);
		}
		if (close(fd) == -1)
			return (perror("close"), FALSE);
		if (new->outfile)
			free(new->outfile);
		new->outfile = ft_strdup(tmp->value);
		if (!new->outfile)
			return (FALSE);
	}
	ft_append_or_trunc(new, tmp);
	return (TRUE);
}

t_boolean	ft_fill_new_command_node(t_tokenizer *token,
		char **envp, t_cmd *new, char ***heredoc)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (TRUE);
		if (tmp->role == STATE_CMD)
			if (ft_is_command(new, tmp, envp) == FALSE)
				return (FALSE);
		if (tmp->role == STATE_REDIR_IN_TARGET
			|| tmp->role == STATE_HEREDOC_DOC)
			if (ft_is_redir_in(new, tmp, heredoc) == FALSE)
				return (FALSE);
		if (tmp->role == STATE_REDIR_OUT_TARGET || tmp->role == STATE_REDIR_OUT
			|| tmp->role == STATE_APPEN_TARGET || tmp->role == STATE_APPEN)
			if (ft_is_redir_out(new, tmp) == FALSE)
				return (FALSE);
		if (tmp->role == STATE_ARGS)
			if (ft_is_args(new, tmp) == FALSE)
				return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
