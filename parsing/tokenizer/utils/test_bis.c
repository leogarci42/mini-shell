/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:36:59 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 18:10:19 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"

t_boolean	ft_has_closing_quote(char *str, int start, char quote)
{
	while (str[start])
	{
		if (str[start] == quote)
			return (TRUE);
		start++;
	}
	return (FALSE);
}

char	*ft_copy_meta_char(char *str, int i, int len)
{
	char	*r_str;
	int		j;

	j = 0;
	r_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!r_str)
		return (NULL);
	while (j < len)
	{
		r_str[j++] = str[i++];
	}
	r_str[j] = '\0';
	return (r_str);
}
