/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:25:55 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/04 16:17:45 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automate.h"

t_boolean	ft_check_heredoc(t_tokenizer next)
{
	if (next.role == STATE_HEREDOC_DOC)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_appen(t_tokenizer next)
{
	if (next.role == STATE_APPEN_TARGET)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_heredoc_doc(t_tokenizer next)
{
	if (next.role == STATE_CMD)
		return (TRUE);
	if (next.role == STATE_HEREDOC)
		return (TRUE);
	if (next.role == STATE_APPEN)
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
	return (FALSE);
}

t_boolean	ft_check_appen_target(t_tokenizer next)
{
	if (next.role == STATE_HEREDOC)
		return (TRUE);
	if (next.role == STATE_REDIR_IN)
		return (TRUE);
	if (next.role == STATE_REDIR_OUT)
		return (TRUE);
	if (next.role == STATE_APPEN)
		return (TRUE);
	if (next.role == STATE_PIPE)
		return (TRUE);
	if (next.role == STATE_AND)
		return (TRUE);
	if (next.role == STATE_OR)
		return (TRUE);
	return (FALSE);
}

t_boolean	ft_check_cmd(t_tokenizer next)
{
	if (next.role == STATE_CMD)
		return (FALSE);
	if (next.role == STATE_REDIR_IN_TARGET)
		return (FALSE);
	if (next.role == STATE_REDIR_OUT_TARGET)
		return (FALSE);
	return (TRUE);
}
