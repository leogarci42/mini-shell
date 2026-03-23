/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:19:51 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/12 17:04:14 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		*str;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	str = d;
	if (d == s)
		return (d);
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		d = d + n;
		s = s + n;
		while (n--)
			*--d = *--s;
	}
	return (str);
}
