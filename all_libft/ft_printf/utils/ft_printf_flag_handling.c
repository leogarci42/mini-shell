/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:06:19 by leogarci          #+#    #+#             */
/*   Updated: 2025/01/25 01:01:17 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

t_printf	*ft_min_flag(t_printf *ret_all, const char *format )
{
	size_t	i;
	int		count;

	i = 0;
	while (format[i] != '-')
		i++;
	count = ft_atoi(&format[i]);
	if (count < 0)
		count += 2;
	else if (count > 0)
		count -= 2;
	printf("\n\n%d\n\n", count);
	printf("Flags: %d\nWidth: %d\nPrecision: %d\n", \
	ret_all->flags, ret_all->width, ret_all->precision);
	return (ret_all);
}

t_printf	*ft_zero_flag(t_printf *ret_all, const char *format)
{
	printf("%s", "work well until now .2");
	format = (const char *)format;
	return (ret_all);
}
