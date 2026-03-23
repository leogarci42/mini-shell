/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:53:59 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/04 11:16:58 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	init_quote_join(char **joined, char *curr, char *quote_char)
{
	size_t	len;

	*quote_char = curr[0];
	len = ft_strlen(curr);
	*joined = malloc(len + 2);
	if (!*joined)
		return (0);
	(*joined)[0] = *quote_char;
	ft_strlcpy(*joined + 1, curr + 1, len);
	return (1);
}

static char	*str_append(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return (NULL);
	if (s1 && len1 > 0)
	{
		ft_strlcpy(result, s1, len1 + 1);
		ft_strlcat(result, " ", len1 + 2);
	}
	else
		result[0] = '\0';
	ft_strlcat(result, s2, len1 + len2 + 2);
	free(s1);
	return (result);
}

int	append_to_joined_and_check_close(char **joined, char *curr)
{
	*joined = str_append(*joined, curr);
	if (!*joined)
		return (0);
	return (1);
}

int	check_and_close_quote(char *curr, char **result, t_join_state *norm)
{
	size_t	len;
	char	*final;

	len = ft_strlen(curr);
	if (len > 0 && curr[len - 1] == norm->quote_char)
	{
		final = ft_strdup(norm->joined);
		if (!final)
			return (0);
		result[norm->k] = final;
		(norm->k)++;
		free(norm->joined);
		norm->joined = NULL;
		return (0);
	}
	return (1);
}

void	add_word_to_result(char **result, int *k, char *curr)
{
	result[*k] = ft_strdup(curr);
	(*k)++;
}
