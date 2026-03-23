/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:31:17 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 22:06:53 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (i == n)
		return (0);
	return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
}
