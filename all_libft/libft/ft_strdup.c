/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:50:58 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/12 14:16:39 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
