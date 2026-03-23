/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:18:22 by leogarci          #+#    #+#             */
/*   Updated: 2025/05/05 22:45:09 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_process_quote_joining(char **split, char **result, t_join_state *st)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (!st->in_quote && is_quote(split[i][0]))
			process_start_of_quote(split[i], result, st);
		else if (st->in_quote)
			process_inside_quote(split[i], result, st);
		else
			add_word_to_result(result, &st->k, split[i]);
		i++;
	}
	handle_unfinished_quote(result, st);
}

void	process_start_of_quote(char *current, char **result, t_join_state *st)
{
	char	*quote_pos;

	st->in_quote = 1;
	st->quote_char = current[0];
	quote_pos = ft_strchr(current + 1, st->quote_char);
	if (quote_pos)
		handle_closed_quote(current, result, st, quote_pos);
	else
		append_partial_to_joined(st, current, ft_strlen(current));
}

void	handle_closed_quote(char *current, char **result, t_join_state *st,
			char *quote_pos)
{
	size_t	quote_len;

	quote_len = quote_pos - current + 1;
	append_partial_to_joined(st, current, quote_len);
	result[st->k++] = ft_strdup(st->joined);
	free(st->joined);
	st->joined = NULL;
	st->in_quote = 0;
	if (current[quote_len])
		add_word_to_result(result, &st->k, current + quote_len);
}

void	process_inside_quote(char *current, char **result, t_join_state *st)
{
	char	*quote_pos;

	quote_pos = ft_strchr(current, st->quote_char);
	if (quote_pos)
		handle_closed_quote(current, result, st, quote_pos);
	else
		append_partial_to_joined(st, current, ft_strlen(current));
}

void	handle_unfinished_quote(char **result, t_join_state *st)
{
	if (st->in_quote && st->joined)
	{
		result[st->k++] = ft_strdup(st->joined);
		free(st->joined);
		st->joined = NULL;
		st->in_quote = 0;
	}
	result[st->k] = NULL;
}
