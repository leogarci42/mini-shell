/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:29 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/18 22:30:51 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_str_len(int nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
		len = 1;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static char	*norm(int nb, unsigned int n_cpy, size_t str_len, char *str)
{
	ft_memset(str, '0', str_len);
	str[str_len] = '\0';
	if (nb < 0)
	{
		n_cpy = (unsigned int)(-nb);
		str[0] = '-';
	}
	else
		n_cpy = (unsigned int)nb;
	while (n_cpy >= 10)
	{
		str[--str_len] = (n_cpy % 10) + '0';
		n_cpy /= 10;
	}
	str[--str_len] = n_cpy + '0';
	return (str);
}

char	*ft_itoa(int nb)
{
	char			*str;
	unsigned int	n_cpy;
	size_t			str_len;

	n_cpy = 0;
	if (nb == 0)
		return (ft_strdup("0"));
	str_len = get_str_len(nb);
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	str = norm(nb, n_cpy, str_len, str);
	return (str);
}
/*
int	main(void)
{
	int	test;
	int	test2;
	int	test3;
	int	test4;
	unsigned int test5;

	test = -2147483648;
	test2 = 2147483647;
	test3 = 0;
	test4 = 456;
	test5 = -621;
	printf("%s\n", ft_itoa(test));
	printf("%s\n", ft_itoa(test2));
	printf("%s\n", ft_itoa(test3));
	printf("%s\n", ft_itoa(test4));
	printf("%s\n", ft_itoa(test5));
	return (0);
}
*/
