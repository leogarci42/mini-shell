/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:03:22 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/13 15:14:01 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tsize;
	void	*ptr;

	tsize = nmemb * size;
	ptr = malloc(tsize);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, tsize);
	return (ptr);
}
