/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:44:21 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/11 21:49:49 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_dst;
	size_t	s_src;

	i = 0;
	s_dst = ft_strlen((char *)dst);
	s_src = ft_strlen((char *)src);
	if (size <= s_dst)
		return (size + s_src);
	else
	{
		while (i < size - s_dst - 1 && src[i])
		{
			dst[s_dst + i] = src[i];
			i++;
		}
		dst[s_dst + i] = '\0';
		return (s_dst + s_src);
	}
	return (0);
}
