/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:30:19 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 21:27:44 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automate.h"

t_boolean	ft_check_args(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (FALSE);
	if (next.role == STATE_REDIR_IN_TARGET)
		return (FALSE);
	if (next.role == STATE_REDIR_OUT_TARGET)
		return (FALSE);
	return (TRUE);
}

t_boolean	ft_check_redir_in(t_tokenizer	next)
{
	if (next.role == STATE_REDIR_IN_TARGET)
		return (TRUE);
	if (next.role == STATE_HEREDOC)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	if (next.role == STATE_APPEN)
		return (TRUE);
	else
		return (FALSE);
}

t_boolean	ft_check_redir_out(t_tokenizer	next)
{
	if (next.role == STATE_REDIR_OUT_TARGET)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_redir_in_target(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	if (next.role == STATE_AND)
		return (TRUE);
	if (next.role == STATE_OR)
		return (TRUE);
	if (next.role == STATE_PIPE)
		return (TRUE);
	if (next.role == STATE_ARGS)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_redir_out_target(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	if (next.role == STATE_AND)
		return (TRUE);
	if (next.role == STATE_OR)
		return (TRUE);
	if (next.role == STATE_PIPE)
		return (TRUE);
	if (next.role == STATE_ARGS)
		return (TRUE);
	if (next.role == STATE_HEREDOC)
		return (TRUE);
	return (FALSE);
}
