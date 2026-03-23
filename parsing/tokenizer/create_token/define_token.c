/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 07:20:59 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 17:53:19 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_boolean	handle_pipe(char **to_tokenize, t_tokenizer **token, int i)
{
	t_tokenizer	*tmp;

	if (to_tokenize[i][0] == '|' && to_tokenize[i][1] != '|')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 1);
	else
		return (FALSE);
	if (!tmp)
		return (FALSE);
	ft_t_tokenizer_add_back(token, tmp);
	return (TRUE);
}

t_boolean	handle_redirects(char **to_tokenize, t_tokenizer **token, int i)
{
	t_tokenizer	*tmp;

	if (to_tokenize[i][0] == '<' && to_tokenize[i][1] != '<')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 2);
	else if (to_tokenize[i][0] == '>' && to_tokenize[i][1] != '>')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 3);
	else if (to_tokenize[i][0] == '>' && to_tokenize[i][1] == '>')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 4);
	else if (to_tokenize[i][0] == '<' && to_tokenize[i][1] == '<')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 5);
	else
		return (FALSE);
	if (!tmp)
		return (FALSE);
	ft_t_tokenizer_add_back(token, tmp);
	return (TRUE);
}

t_boolean	handle_double_ops(char **to_tokenize, t_tokenizer **token, int i)
{
	t_tokenizer	*tmp;

	if (to_tokenize[i][0] == 38 && to_tokenize[i][1] == 38)
		tmp = ft_t_tokenizer_new(to_tokenize[i], 6);
	else if (to_tokenize[i][0] == '|' && to_tokenize[i][1] == '|')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 7);
	else
		return (FALSE);
	if (!tmp)
		return (FALSE);
	ft_t_tokenizer_add_back(token, tmp);
	return (TRUE);
}

t_boolean	handle_parentheses(char **to_tokenize, t_tokenizer **token, int i)
{
	t_tokenizer	*tmp;
	int			j;

	j = 0;
	tmp = NULL;
	while (to_tokenize[i][j])
	{
		if (to_tokenize[i][j] == '(')
		{
			tmp = ft_t_tokenizer_new(to_tokenize[i], 8);
			break ;
		}
		else if (to_tokenize[i][j] == ')')
		{
			tmp = ft_t_tokenizer_new(to_tokenize[i], 9);
			break ;
		}
		j++;
	}
	if (!tmp)
		return (FALSE);
	ft_t_tokenizer_add_back(token, tmp);
	return (TRUE);
}

t_boolean	handle_quotes(char **to_tokenize, t_tokenizer **token, int i)
{
	t_tokenizer	*tmp;

	if (to_tokenize[i][0] == '"')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 11);
	else if (to_tokenize[i][0] == '\'')
		tmp = ft_t_tokenizer_new(to_tokenize[i], 10);
	else
		return (FALSE);
	if (!tmp)
		return (FALSE);
	ft_t_tokenizer_add_back(token, tmp);
	return (TRUE);
}
