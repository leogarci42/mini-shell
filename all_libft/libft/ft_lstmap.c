/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:58:34 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/20 00:20:13 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*next;
	void	*content;

	current = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		next = ft_lstnew(content);
		if (!next)
		{
			del(content);
			ft_lstclear(&current, del);
			return (NULL);
		}
		ft_lstadd_back(&current, next);
		lst = lst->next;
	}
	return (current);
}
