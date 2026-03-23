/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:31:49 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 12:50:31 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automate.h"

t_boolean	ft_check_pipe(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	if (next.role == STATE_HEREDOC)
		return (TRUE);
	if (next.role == STATE_APPEN)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_and(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_or(t_tokenizer	next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_part2(t_tokenizer curr, t_tokenizer next)
{
	if (curr.role == STATE_PIPE)
	{
		if (!ft_check_pipe(next))
			return (TRUE);
		else
			return (FALSE);
	}
	if (!next.value)
		return (TRUE);
	if (curr.role == STATE_APPEN)
		if (!ft_check_appen(next))
			return (TRUE);
	if (curr.role == STATE_APPEN_TARGET)
		if (!ft_check_appen_target(next))
			return (TRUE);
	if (curr.role == STATE_HEREDOC)
		if (!ft_check_heredoc(next) && next.value)
			return (TRUE);
	if (curr.role == STATE_HEREDOC_DOC)
		if (!ft_check_heredoc_doc(next))
			return (TRUE);
	return (FALSE);
}

t_boolean	ft_check(t_tokenizer curr, t_tokenizer next)
{
	if (curr.role == NONE)
		return (FALSE);
	if (curr.role == STATE_CMD)
		if (!ft_check_cmd(next))
			return (TRUE);
	if (curr.role == STATE_ARGS)
		if (!ft_check_args(next))
			return (TRUE);
	if (curr.role == STATE_REDIR_IN && next.value)
		if (!ft_check_redir_in(next))
			return (TRUE);
	if (curr.role == STATE_REDIR_OUT && next.value)
		if (!ft_check_redir_out(next))
			return (TRUE);
	if (curr.role == STATE_REDIR_IN_TARGET && next.value)
		if (!ft_check_redir_in_target(next))
			return (TRUE);
	if (curr.role == STATE_REDIR_OUT_TARGET && next.value)
		if (!ft_check_redir_out_target(next))
			return (TRUE);
	return (ft_check_part2(curr, next));
}
