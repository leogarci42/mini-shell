/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:20:41 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/14 14:21:18 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	a;
	char			*str;

	if (!s || !f)
		return (NULL);
	a = (unsigned int)ft_strlen((char *)s);
	str = malloc((a + 1) * sizeof(char));
	if (!str)
		return (NULL);
	a = 0;
	while (s[a])
	{
		str[a] = f(a, s[a]);
		a++;
	}
	str[a] = 0;
	return (str);
}
