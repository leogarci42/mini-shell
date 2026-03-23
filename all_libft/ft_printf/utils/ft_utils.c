/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:29:43 by leogarci          #+#    #+#             */
/*   Updated: 2024/12/14 22:28:26 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*ft_hexa(t_printf *ret_all)
{
	long long				num;
	char					*base;

	base = LOW_HEXBASE;
	num = va_arg(ret_all->args, long long);
	if (ret_all->ind == 'x')
		base = LOW_HEXBASE;
	else if (ret_all->ind == 'X')
		base = UP_HEXBASE;
	ft_putnbr_hexa(num, base, &ret_all->len);
	return (ret_all);
}

void	ft_putnbr_hexa(unsigned int n, char *base, size_t *len)
{
	if (n >= 16)
		ft_putnbr_hexa(n / 16, base, len);
	write(1, &base[n % 16], 1);
	*len += 1;
}
