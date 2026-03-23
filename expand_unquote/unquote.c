/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:31:49 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/15 12:04:41 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_get_len(char *str, char q)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != q)
		len++;
	return (len);
}

t_boolean	ft_unquoting(t_unquote *unquote, char *str, char q, int start)
{
	int		len;
	char	*dup;

	if (!unquote->new_str)
		unquote->new_str = ft_strdup("");
	len = ft_get_len(&str[start + 1], q);
	dup = ft_substr(str, start + 1, len);
	unquote->new_str = ft_strjoin_free(unquote->new_str, dup);
	unquote->pos = start + len + 2;
	free (dup);
	unquote->q = 0;
	unquote->i = unquote->pos;
	return (TRUE);
}

t_boolean	ft_copying(t_unquote *unquote, char *str, int start)
{
	int		len;
	char	*dup;

	if (!unquote->new_str)
		unquote->new_str = ft_strdup("");
	len = start;
	if (str[start] == '\'' || str[start] == '"')
		len++;
	while (str[len] != '\0' && str[len] != '"' && str[len] != '\'')
		len++;
	dup = ft_substr(str, start, len - start);
	unquote->new_str = ft_strjoin_free(unquote->new_str, dup);
	unquote->pos = len;
	free (dup);
	unquote->i = unquote->pos;
	return (TRUE);
}

char	*ft_unquote(char *str)
{
	t_unquote	unquote;

	if (ft_strlen(str) == 0)
		return (free(str), ft_strdup(""));
	ft_memset(&unquote, 0, sizeof(t_unquote));
	while (str[unquote.i])
	{
		if (str[unquote.i] == '"' || str[unquote.i] == '\'')
		{
			if (!ft_has_closing_quote(str, unquote.i + 1, str[unquote.i]))
				unquote.q = str[unquote.i];
		}
		if (unquote.q != 0)
		{
			if (ft_unquoting(&unquote, str, unquote.q, unquote.i) == FALSE)
				return (NULL);
		}
		else
		{
			if (ft_copying(&unquote, str, unquote.i) == FALSE)
				return (NULL);
		}
	}
	free(str);
	return (unquote.new_str);
}
