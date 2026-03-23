/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:50:53 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/12 14:21:08 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			str = (char *)&s[i];
			return (str);
		}
		i--;
	}
	return (0);
}
/*#include <string.h>
int	main(void)
{
	char	*s = "iwuty cwhueoqncrxoel 464413 6663";
	char	*str = ft_strrchr(s, 't' + 256);
	char	*str2 = strrchr(s, 't' + 256);

	printf("ft: %s\nog: %s\n", str, str2);
}*/
