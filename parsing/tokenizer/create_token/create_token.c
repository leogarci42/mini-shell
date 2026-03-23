/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:58:35 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 17:54:30 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_tokenizer	*ft_t_tokenizer_new(char *to_tokenize, uint8_t i)
{
	t_tokenizer	*token;

	token = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!token)
		return (NULL);
	token->value = to_tokenize;
	token->type = i;
	token->role = NONE;
	token->next = NULL;
	return (token);
}

t_boolean	ft_t_tokenizer_add_back(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*mv;

	if (!new)
		return (FALSE);
	if (*token == NULL)
	{
		*token = new;
		return (TRUE);
	}
	mv = *token;
	while (mv->next)
		mv = mv->next;
	mv->next = new;
	return (TRUE);
}

static t_boolean	check_if_meta_char(char **to_tokenize,
					t_tokenizer **token, int i)
{
	if (!handle_parentheses(to_tokenize, token, i))
		return (TRUE);
	if (!handle_pipe(to_tokenize, token, i))
		return (TRUE);
	if (!handle_redirects(to_tokenize, token, i))
		return (TRUE);
	if (!handle_double_ops(to_tokenize, token, i))
		return (TRUE);
	if (!handle_quotes(to_tokenize, token, i))
		return (TRUE);
	return (FALSE);
}

static void	check_if_words(char **to_tokenize, t_tokenizer **token,
						int i)
{
	t_tokenizer	*tmp;

	if (!ft_ismetachar(to_tokenize[i][0]))
	{
		tmp = ft_t_tokenizer_new(to_tokenize[i], 0);
		if (!tmp)
			return ;
		ft_t_tokenizer_add_back(token, tmp);
	}
	else
	{
		tmp = ft_t_tokenizer_new(to_tokenize[i], NOTHING);
		if (!tmp)
			return ;
		ft_t_tokenizer_add_back(token, tmp);
	}
}

t_boolean	ft_tokenize_array(char **to_tokenize, t_tokenizer **token)
{
	int	i;

	i = 0;
	while (to_tokenize[i] != NULL)
	{
		if (check_if_meta_char(to_tokenize, token, i))
			check_if_words(to_tokenize, token, i);
		i++;
	}
	if (to_tokenize[0] == NULL)
		return (FALSE);
	return (TRUE);
}
