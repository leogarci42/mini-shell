/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:00:00 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/15 13:54:54 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_init_cmd_list(t_cmd **new)
{
	*new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*new)
		return (FALSE);
	(*new)->args = NULL;
	(*new)->infile = NULL;
	(*new)->outfile = NULL;
	(*new)->next = NULL;
	(*new)->path = NULL;
	(*new)->redir_type = 0;
	return (TRUE);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*mv;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	mv = *lst;
	while (mv->next)
		mv = mv->next;
	mv->next = new;
}

t_boolean	ft_expand_tokenizer(t_tokenizer *token, char **env_minishell,
	int *backup)
{
	t_tokenizer	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->role == STATE_CMD || tmp->role == STATE_ARGS
			|| tmp->role == STATE_APPEN_TARGET || tmp->role == STATE_HEREDOC_DOC
			|| tmp->role == STATE_REDIR_IN_TARGET
			|| tmp->role == STATE_REDIR_OUT_TARGET)
		{
			tmp->value = ft_expander(tmp->value, env_minishell, backup);
			if (!tmp->value)
				return (FALSE);
			tmp->value = ft_unquote(tmp->value);
			if (!tmp->value)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

t_boolean	ft_create_command(t_cmd **command, t_tokenizer *token,
		char **env_minishell, t_norm norm)
{
	t_cmd	*new;

	new = NULL;
	if (ft_expand_tokenizer(token, env_minishell, norm.backup) == FALSE)
		return (FALSE);
	if (ft_init_cmd_list(&new) == FALSE)
		return (FALSE);
	if (ft_fill_new_command_node(token, env_minishell, new,
			&norm.heredoc) == FALSE)
		return (ft_free_cmd_and_next(new), FALSE);
	ft_cmdadd_back(command, new);
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		ft_create_command(command, token->next, env_minishell, norm);
	return (TRUE);
}
