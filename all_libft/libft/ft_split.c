/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:05:42 by leogarci          #+#    #+#             */
/*   Updated: 2024/11/18 22:08:10 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**free_all(char **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**ft_split_v2(char const *s, char c, char **res)
{
	int		i;
	int		len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		while (len > 0 && s[len - 1] == c)
			len--;
		if (len > 0)
		{
			res[i++] = ft_substr(s, 0, len);
			if (!res[i - 1])
				return (free_all(res, i - 1));
		}
		s += len;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_split_v2(s, c, res);
	return (res);
}
/*
#include <stdio.h>

int main(void)
{
    char **result = ft_split("                 olol ", ' ');
    for (int i = 0; result[i] != NULL; i++)
    {
        printf("Substring %d: '%s'\n", i, result[i]);
        free(result[i]);
    }
    free(result);
    return (0);
}
*/
