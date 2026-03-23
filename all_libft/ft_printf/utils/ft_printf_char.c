/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:12:30 by leogarci          #+#    #+#             */
/*   Updated: 2024/12/14 22:27:43 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*ft_char(t_printf *ret_all)
{
	char	c;

	c = (char)va_arg(ret_all->args, int);
	ret_all->len += write(1, &c, 1);
	return (ret_all);
}

t_printf	*ft_str(t_printf *ret_all)
{
	char	*str;
	int		i;

	i = 0;
	str = va_arg(ret_all->args, char *);
	if (!str)
	{
		ret_all->len += write(1, "(null)", 6);
		return (ret_all);
	}
	while (str[i])
		ret_all->len += write(1, &str[i++], 1);
	return (ret_all);
}
