/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:18 by leogarci          #+#    #+#             */
/*   Updated: 2024/12/14 22:27:58 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*ft_p_hexa(t_printf *ret_all)
{
	char					*base;
	unsigned long long		test;

	base = LOW_HEXBASE;
	test = va_arg(ret_all->args, unsigned long long);
	if (ret_all->ind == 'x')
		base = LOW_HEXBASE;
	else if (ret_all->ind == 'X')
		base = UP_HEXBASE;
	else if (ret_all->ind == 'p')
	{
		if (!test)
		{
			ret_all->len += write(1, "(nil)", 5);
			return (ret_all);
		}
		write(1, "0x", 2);
		ret_all->len += 2;
	}
	ft_putnbr_p_hexa(test, base, &ret_all->len);
	return (ret_all);
}

void	ft_putnbr_p_hexa(unsigned long long n, char *base, size_t *len)
{
	if (n >= 16)
		ft_putnbr_p_hexa(n / 16, base, len);
	write(1, &base[n % 16], 1);
	*len += 1;
}
