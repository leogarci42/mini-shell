/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:48:23 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/12 14:57:01 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	int				i;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (n--)
		str[i++] = ch;
	return (str);
}
