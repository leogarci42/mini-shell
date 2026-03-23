/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:58 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/14 19:02:49 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

# define LOW_HEXBASE "0123456789abcdef"
# define UP_HEXBASE "0123456789ABCDEF"

# define FLAG_MIN 1
# define FLAG_ZERO  2

typedef struct s_printf
{
	va_list	args;
	va_list	args_copy;
	size_t	len;
	char	ind;
	void	*to_print;
	int		flags;
	int		width;
	int		precision;
}	t_printf;

t_printf	*ft_min_flag(t_printf *ret_all, const char *format);
t_printf	*ft_zero_flag(t_printf *ret_all, const char *format);
int			ft_printf(const char *format, ...);
t_printf	*ft_format(t_printf *ret_all, const char *format);
t_printf	*call_everything(t_printf *ret_all, const char *format);
t_printf	*ft_int(t_printf *ret_all);
t_printf	*ft_char(t_printf *ret_all);
t_printf	*ft_str(t_printf *ret_all);
t_printf	*ft_p_hexa(t_printf *ret_all);
t_printf	*ft_mod(t_printf *ret_all);
t_printf	*init_struct(t_printf *ret_all);
void		ft_write(int width, char c, size_t *len);
t_printf	*ft_putnbr(long long int n, t_printf *ret_all);
t_printf	*ft_u_int(t_printf *ret_all);
void		ft_putnbr_p_hexa(unsigned long long n, char *base, size_t *len);
void		ft_putnbr_hexa(unsigned int n, char *base, size_t *len);
t_printf	*ft_hexa(t_printf *ret_all);
t_printf	*add_flags(t_printf *ret_all, const char *format);
int			ft_atoi(const char *str);
#endif
