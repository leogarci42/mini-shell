/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:45:52 by leogarci          #+#    #+#             */
/*   Updated: 2025/01/25 18:31:29 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*init_struct(t_printf *ret_all)
{
	ret_all->flags = 0;
	ret_all->width = 0;
	ret_all->precision = -1;
	ret_all->ind = '\0';
	ret_all->to_print = NULL;
	return (ret_all);
}

static void	ft_flags(t_printf *ret_all, const char **format)
{
	while (**format == '-' || **format == '0')
	{
		if (**format == '-')
			ret_all->flags |= FLAG_MIN;
		else if (**format == '0')
			ret_all->flags |= FLAG_ZERO;
		(*format)++;
	}
	if (ret_all->flags & FLAG_MIN)
		ret_all->flags &= ~FLAG_ZERO;
}

static void	ft_width(t_printf *ret_all, const char **format)
{
	if (**format >= '0' && **format <= '9')
	{
		ret_all->width = 0;
		while (**format >= '0' && **format <= '9')
		{
			ret_all->width = ret_all->width * 10 + (**format - '0');
			(*format)++;
		}
	}
	else if (**format == '*')
	{
		ret_all->width = va_arg(ret_all->args, int);
		if (ret_all->width < 0)
		{
			ret_all->flags |= FLAG_MIN;
			ret_all->width = -ret_all->width;
		}
		(*format)++;
	}
}

static void	ft_precision(t_printf *ret_all, const char **format)
{
	if (**format == '.')
	{
		(*format)++;
		if (**format >= '0' && **format <= '9')
		{
			ret_all->precision = 0;
			while (**format >= '0' && **format <= '9')
			{
				ret_all->precision = ret_all->precision * 10 + (**format - '0');
				(*format)++;
			}
		}
		else if (**format == '*')
		{
			ret_all->precision = va_arg(ret_all->args, int);
			if (ret_all->precision < 0)
				ret_all->precision = -1;
			(*format)++;
		}
		else
			ret_all->precision = 0;
	}
}

t_printf	*ft_format(t_printf *ret_all, const char *format)
{
	init_struct(ret_all);
	ft_flags(ret_all, &format);
	ft_width(ret_all, &format);
	ft_precision(ret_all, &format);
	if (*format && (*format == 'd' || *format == 'i' || *format == 'u' || \
					*format == 'x' || *format == 'X' || *format == 'c' || \
					*format == 's' || *format == 'p' || *format == '%'))
		ret_all->ind = *format;
	else
		return (NULL);
	return (ret_all);
}
