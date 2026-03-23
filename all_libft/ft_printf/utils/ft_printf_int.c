/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:13:07 by leogarci          #+#    #+#             */
/*   Updated: 2024/12/14 22:27:20 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*ft_int(t_printf *ret_all)
{
	long long int	num;

	num = va_arg(ret_all->args, int);
	ret_all = ft_putnbr(num, ret_all);
	return (ret_all);
}

t_printf	*ft_u_int(t_printf *ret_all)
{
	unsigned int	num;

	num = va_arg(ret_all->args, int);
	ret_all = ft_putnbr(num, ret_all);
	return (ret_all);
}

t_printf	*ft_putnbr(long long int n, t_printf *ret_all)
{
	long long int	tmp;

	if (n < 0)
	{
		ret_all->len += write(1, "-", 1);
		n = -n;
		ft_putnbr(n, ret_all);
	}
	else if (n >= 10)
	{
		ft_putnbr((n / 10), ret_all);
		ft_putnbr((n % 10), ret_all);
	}
	else
	{
		tmp = n + 48;
		ret_all->len += write(1, &tmp, 1);
	}
	return (ret_all);
}
