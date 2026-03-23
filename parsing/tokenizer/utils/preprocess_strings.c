/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 03:06:23 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 15:29:08 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_space_for_op(const char *input, int i, int *len)
{
	if ((input[i] == '>' && input[i + 1] == '>') || \
		(input[i] == '<' && input[i + 1] == '<') || \
		(input[i] == '&' && input[i + 1] == '&') || \
		(input[i] == '|' && input[i + 1] == '|'))
	{
		*len += 4;
		return (1);
	}
	*len += 2;
	return (0);
}

static void	ft_copy_op_with_spaces(char *result, const char *input,
	int *i, int *j)
{
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '&' && input[*i + 1] == '&')
		|| (input[*i] == '|' && input[*i + 1] == '|'))
	{
		result[(*j)++] = ' ';
		result[(*j)++] = input[*i];
		result[(*j)++] = input[*i + 1];
		result[(*j)++] = ' ';
		(*i)++;
	}
	else
	{
		result[(*j)++] = ' ';
		result[(*j)++] = input[*i];
		result[(*j)++] = ' ';
	}
}

static void	ft_calc_spaces(const char *input, int *len)
{
	int	i;
	int	indquote;
	int	insquote;

	i = 0;
	indquote = 0;
	insquote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !insquote)
			indquote = input[i];
		else if (input[i] == '\'' && !indquote)
			insquote = input[i];
		if (!indquote && !insquote && (input[i] == '|' || input[i] == '<'
				|| input[i] == '>'))
		{
			i += ft_add_space_for_op(input, i, len);
		}
		(*len)++;
		i++;
	}
}

static void	ft_fill_result(char *result, const char *input)
{
	int	i;
	int	j;
	int	indquote;
	int	insquote;

	i = 0;
	j = 0;
	indquote = 0;
	insquote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !insquote)
			indquote = input[i];
		else if (input[i] == '\'' && !indquote)
			insquote = input[i];
		if (!indquote && !insquote && (input[i] == '|' || input[i] == '<'
				|| input[i] == '>'))
			ft_copy_op_with_spaces(result, input, &i, &j);
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
}

char	*ft_preprocess_cmd_string(char *input)
{
	char	*result;
	int		len;

	len = 0;
	ft_calc_spaces(input, &len);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_fill_result(result, input);
	free(input);
	return (result);
}
