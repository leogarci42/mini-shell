/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:09:33 by leogarci          #+#    #+#             */
/*   Updated: 2025/04/19 18:38:23 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	i = 0;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
