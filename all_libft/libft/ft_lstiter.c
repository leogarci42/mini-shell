/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:20:09 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/19 23:27:14 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter( t_list *lst, void (*f)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !f)
		return ;
	current = lst;
	while (current)
	{
		next = current->next;
		f(current->content);
		current = next;
	}
}
