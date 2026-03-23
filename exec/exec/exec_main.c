/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:12:17 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/15 11:34:28 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_close_unlink_heredoc(void)
{
	int		i;
	char	*path;

	i = 0;
	while (1)
	{
		path = ft_get_heredoc_path(i);
		if (!path)
			perror(path);
		else
		{
			if (access(path, R_OK) == 0)
			{
				if (unlink(path) == -1)
					perror(path);
			}
			else
				break ;
			free(path);
		}
		i++;
	}
	free(path);
}

static int	ft_command_count(t_tokenizer *token)
{
	int			count;
	t_tokenizer	*tmp;

	tmp = token;
	count = 1;
	while (tmp)
	{
		if (tmp->role == STATE_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_boolean	ft_exec_minishell(t_tokenizer **tokens, char ***env_minishell,
	int *backup)
{
	t_cmd	*command;
	int		nb_cmd;
	t_norm	norm;

	command = NULL;
	norm.backup = backup;
	norm.heredoc = ft_exec_heredoc(*tokens, norm.backup, *env_minishell);
	if (!norm.heredoc)
		return (ft_free_token_list(tokens), FALSE);
	g_status = STATUS_OK;
	nb_cmd = ft_command_count(*tokens);
	if (ft_create_command(&command, *tokens, *env_minishell, norm) == FALSE)
		return (ft_free_command_lst(&command),
			ft_free_token_list(tokens), ft_free_array(norm.heredoc), FALSE);
	ft_free_array(norm.heredoc);
	ft_free_token_list(tokens);
	if (nb_cmd > 0)
	{
		if (ft_exec_cmd(command, env_minishell, nb_cmd, norm.backup) == FALSE)
			return (FALSE);
	}
	else
		ft_free_command_lst(&command);
	ft_close_unlink_heredoc();
	return (TRUE);
}
