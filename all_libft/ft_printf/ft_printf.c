/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:09:08 by leogarci          #+#    #+#             */
/*   Updated: 2024/12/14 21:13:55 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	*call_everything(t_printf *ret_all, const char *format)
{
	if (ret_all->flags)
		ret_all = add_flags(ret_all, format);
	else if (ret_all->ind == 'd' || ret_all->ind == 'i')
		ret_all = ft_int(ret_all);
	else if (ret_all->ind == 'u')
		ret_all = ft_u_int(ret_all);
	else if (ret_all->ind == 'c')
		ret_all = ft_char(ret_all);
	else if (ret_all->ind == 's')
		ret_all = ft_str(ret_all);
	else if (ret_all->ind == 'p' )
		ret_all = ft_p_hexa(ret_all);
	else if (ret_all->ind == 'x' || ret_all->ind == 'X')
		ret_all = ft_hexa(ret_all);
	else if (ret_all->ind == '%')
		ret_all = ft_mod(ret_all);
	else
	{
		write(1, &ret_all->ind, 1);
		ret_all->len++;
	}
	return (ret_all);
}

int	ft_printf(const char *format, ...)
{
	t_printf			ret_all;
	unsigned long		i;

	ret_all.len = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(ret_all.args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!(ft_format(&ret_all, &format[i])))
				return (-1);
			if (!(call_everything(&ret_all, format)))
				return (-1);
		}
		else
			ret_all.len += write(1, &format[i], 1);
		i++;
	}
	va_end(ret_all.args);
	return ((int)ret_all.len);
}
