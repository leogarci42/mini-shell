/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_aware.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:39:11 by leogarci          #+#    #+#             */
/*   Updated: 2025/05/31 19:39:14 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_ischarset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	tab_size(char *str, char *charset)
{
	int		i;
	int		size;
	int		suitch;
	char	quote;

	size = 0;
	suitch = 1;
	i = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == '\0')
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		if (suitch && !ft_ischarset(str[i], charset) && quote == '\0')
		{
			size++;
			suitch = 0;
		}
		if (ft_ischarset(str[i], charset) && quote == '\0')
			suitch = 1;
		i++;
	}
	return (size);
}

int	set_tab(char *str, char *charset, char **result)
{
	int	i;
	int	start;
	int	end;
	int	j;

	j = 0;
	i = 0;
	while (ft_ischarset(str[i], charset))
		i++;
	while (str[i])
	{
		start = i;
		while (str[i] && !ft_ischarset(str[i], charset))
			i++;
		end = i;
		result[j] = malloc(sizeof(char) * (end - start + 1));
		if (result[j] == NULL)
			return (0);
		ft_strncpy(result[j], str + start, end - start);
		j++;
		while (str[i] && ft_ischarset(str[i], charset))
			i++;
	}
	result[j] = 0;
	return (1);
}

char	**split_quote_aware(char *str, char *charset)
{
	char	**result;

	result = malloc(sizeof(char *) * (tab_size(str, charset) + 1));
	if (result == NULL)
		return (NULL);
	if (!set_tab(str, charset, result))
		return (NULL);
	return (result);
}
