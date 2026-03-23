/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:35:34 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/13 14:56:45 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			num;
	unsigned char	*str;

	str = (unsigned char *)s;
	num = 0;
	while (num < n)
	{
		if (str[num] == (unsigned char)c)
			return (str + num);
		num++;
	}
	return (NULL);
}
/*
#include <string.h>
int	main(void)
{
	char	*str = "/|\x12\xff\x09\0\x42\042\0\42|\\";
	int	size = 12;
	printf("Mine:%s\n", (char *)ft_memchr(str, '\0', size));
	printf("Real:%s\n", (char *)memchr(str, '\0', size));
	return (0);
}
*/
