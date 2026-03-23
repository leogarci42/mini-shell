/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_modulo_and_flags.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:13:29 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/14 19:03:15 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return ((nb) * sign);
}

t_printf	*add_flags(t_printf *ret_all, const char *format)
{
	if (ret_all->flags == 1)
		ret_all = ft_min_flag(ret_all, format);
	if (ret_all->flags == 2)
		ret_all = ft_zero_flag(ret_all, format);
	return (ret_all);
}

t_printf	*ft_mod(t_printf *ret_all)
{
	write(1, "%", 1);
	ret_all->len++;
	return (ret_all);
}
