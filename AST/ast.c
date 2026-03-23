/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:06:32 by leogarci          #+#    #+#             */
/*   Updated: 2025/05/31 19:50:42 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_boolean	ft_check_if_pipe(t_ast *tmp, t_tokenizer *tmp_t)
{
	while (tmp_t)
	{
		if (tmp_t->type == PIPE)
			return (TRUE);
		tmp_t = tmp_t->next;
	}
	return (FALSE);
}

t_boolean	ft_check_redir(t_ast *head_ast, t_tokenizer *head_token)
{
	while (head_token)
	{
		if (head_token->type == REDIR_IN)
			return (TRUE);
		if (head_token->type == REDIR_OUT)
			return (TRUE);
		if (head_token->type == REDIR_APPEN)
			return (TRUE);
		if (head_token->type == REDIR_HEREDOC)
			return (TRUE);
		head_token = head_token->next;
	}
	return (FALSE);
}

t_boolean	init_t_ast(t_ast *head_ast, t_tokenizer *head_token)
{
	t_ast		*tmp;
	t_tokenizer	*tmp_t;

	tmp = head_ast;
	tmp_t = head_token;
	if (!ft_check_redir(tmp, tmp_t))
	{
		head_ast = (t_ast *)malloc(t_ast);
		if (!head_ast)
			return (FALSE);
		if (head_token->type == REDIR_IN)
			head_ast->type = REDIR_IN;
		if (head_token->type == REDIR_OUT)
			head_ast->type = REDIR_OUT;
		if (head_token->type == REDIR_APPEN)
			head_ast->type = REDIR_APPEN;
		if (head_token->type == REDIR_HEREDOC)
			head_ast->type = REDIR_HEREDOC;
	}
	if (!ft_check_if_pipe(tmp, tmp_t))
	{
		head_ast = (t_ast *)malloc(t_ast);
		if (!head_ast)
			return (FALSE);
		head_ast->type = PIPE;
		head_ast->value = tmp->value;
	}
	if (!ft_check_if_cmd(tmp, tmp_t))
	{
		tmp = (t_ast *)malloc(t_ast);
		if (!head_ast)
			return (FALSE);
		tmp->type == STATE_CMD;
		tmp->value = tmp_t->value;
	}
	return (TRUE);
}

t_boolean	ft_make_t_ast(t_ast *head_ast, t_tokenizer *head_token)
{
	t_ast		*tmp;
	t_tokenizer	*tmp_t;

	tmp = head_ast;
	tmp_t = head_token;
	while (tmp_t)
		tmp_t = tmp->next;
}

t_boolean	ft_ast(t_tokenizer *head_token)
{
	t_ast	*head_ast;

	if (init_t_ast(head_ast, head_token))
		return (FALSE);
	if (ft_make_t_ast(head_ast, head_token))
		return (FALSE);
}
