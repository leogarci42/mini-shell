/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_automate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:59:17 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 12:48:17 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automate.h"
#include "minishell.h"

t_boolean	ft_automate(t_tokenizer *head, int *backup)
{
	t_tokenizer	*curr;
	t_tokenizer	dummy;

	dummy = (t_tokenizer){0};
	curr = head;
	if (curr->role == STATE_PIPE)
	{
		backup[2] = 2;
		return (printf(SA, curr->value), FALSE);
	}
	while (curr->next)
	{
		if (ft_check(*curr, *curr->next))
		{
			backup[2] = 2;
			return (printf(SA, curr->value), FALSE);
		}
		curr = curr->next;
	}
	if (ft_check(*curr, dummy))
	{
		backup[2] = 2;
		return (printf(SA, curr->value), FALSE);
	}
	return (TRUE);
}
