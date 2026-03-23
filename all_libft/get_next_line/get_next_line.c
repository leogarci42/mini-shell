/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:42:49 by leogarci          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:28 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checkline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

char	*ft_current(char *str)
{
	char	*ret_str;
	int		len;
	int		i;
	int		s_char;

	if (!str || *str == '\0')
		return (NULL);
	len = checkline(str);
	if (str[len] == '\n')
		s_char = 1;
	else
		s_char = 0;
	ret_str = malloc((len + s_char + 1) * sizeof(char));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret_str[i] = str[i];
		i++;
	}
	if (s_char)
		ret_str[i++] = '\n';
	ret_str[i] = '\0';
	return (ret_str);
}

char	*ft_clean(char *str)
{
	int		i;
	int		j;
	char	*ret_str;

	i = checkline(str);
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	ret_str = malloc((ft_strlen1(str) - i + 1) * sizeof(char));
	if (!ret_str)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		ret_str[j++] = str[i++];
	ret_str[j] = '\0';
	free(str);
	return (ret_str);
}

char	*get_next_line(int fd)
{
	static char	*all_str;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!all_str)
	{
		all_str = malloc(1);
		if (!all_str)
			return (NULL);
		all_str[0] = '\0';
	}
	all_str = get_a_line(fd, all_str);
	if (!all_str)
		return (NULL);
	str = ft_current(all_str);
	all_str = ft_clean(all_str);
	return (str);
}
