/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:15:35 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 13:50:01 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"

int	ft_parse_word(char *str, int i, int j)
{
	char	in_quote;

	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && in_quote == 0)
		{
			if (!ft_has_closing_quote(str, i, str[i]))
				in_quote = str[i];
		}
		else if (str[i] == in_quote)
			in_quote = 0;
		if (in_quote == 0)
		{
			if (ft_strncmp(&str[i], "||", 2) == 0
				|| ft_strncmp(&str[i], "&&", 2) == 0)
				break ;
			if (ft_isspace(str[i]))
				break ;
		}
		i++;
	}
	return (i - j);
}

int	ft_word(char *str, int i)
{
	int	j;

	j = i;
	if (ft_strncmp(&str[i], "||", 2) != 0 && ft_strncmp(&str[i], "&&", 2) != 0)
		return (ft_parse_word(str, i, j));
	return (0);
}

int	ft_count_token(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_word(str, i))
		{
			j++;
			i += ft_word(str, i);
		}
		else if (ft_strncmp(&str[i], "||", 2) == 0
			|| ft_strncmp(&str[i], "&&", 2) == 0)
		{
			i += 2;
			j++;
		}
		else
			i++;
	}
	return (j);
}

char	**ft_fill_split(char **split_not_split, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_word(str, i))
		{
			split_not_split[j] = ft_substr(str, i, ft_word(str, i));
			j++;
			i += ft_word(str, i);
		}
		else if (ft_strncmp(&str[i], "||", 2) == 0
			|| ft_strncmp(&str[i], "&&", 2) == 0)
		{
			split_not_split[j++] = ft_copy_meta_char(str, i, 2);
			i += 2;
		}
		else
			i++;
	}
	split_not_split[j] = NULL;
	free(str);
	return (split_not_split);
}

char	**ft_no_split(char *str)
{
	char	**split_not_split;
	char	*joined_str;
	int		token_count;

	joined_str = ft_strjoin(str, " ");
	token_count = ft_count_token(joined_str);
	split_not_split = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!split_not_split)
		exit(1);
	return (ft_fill_split(split_not_split, joined_str));
}
