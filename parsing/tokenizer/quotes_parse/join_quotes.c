/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:22 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/04 11:18:44 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	count_joined_words_init(t_count_join_words *norm)
{
	norm->i = 0;
	norm->count = 0;
	norm->in_quote = 0;
}

int	count_joined_words(char **split)
{
	t_count_join_words	norm;

	count_joined_words_init(&norm);
	while (split[norm.i])
	{
		if (!norm.in_quote && is_quote(split[norm.i][0]))
		{
			norm.in_quote = 1;
			norm.quote_char = split[norm.i][0];
		}
		else if (norm.in_quote)
		{
			if (ft_strchr(split[norm.i], norm.quote_char))
			{
				norm.in_quote = 0;
				norm.count++;
			}
		}
		else
			norm.count++;
		norm.i++;
	}
	if (norm.in_quote)
		norm.count++;
	return (norm.count);
}

int	append_partial_to_joined(t_join_state *st, const char *src, size_t len)
{
	char	*new_joined;
	size_t	old_len;
	size_t	total_len;

	old_len = 0;
	if (st->joined)
		old_len = ft_strlen(st->joined);
	if (old_len > 0)
		total_len = old_len + 1 + len + 1;
	else
		total_len = len + 1;
	new_joined = malloc(total_len);
	if (!new_joined)
		return (0);
	if (st->joined)
		ft_strlcpy(new_joined, st->joined, old_len + 1);
	else
		new_joined[0] = '\0';
	if (old_len > 0)
		ft_strlcat(new_joined, " ", total_len);
	ft_strlcat(new_joined, src, total_len);
	if (st->joined)
		free(st->joined);
	st->joined = new_joined;
	return (1);
}

void	ft_join_quotes_in_split(char ***split_ptr)
{
	char			**split;
	char			**result;
	t_join_state	st;

	split = *split_ptr;
	result = malloc(sizeof(char *) * (count_joined_words(split) + 1));
	if (!result)
		return ;
	st.k = 0;
	st.in_quote = 0;
	st.joined = NULL;
	ft_process_quote_joining(split, result, &st);
	free_split(split);
	*split_ptr = result;
}
