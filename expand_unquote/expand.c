/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:13:20 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 12:04:37 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_variable(char *str, char **env_minishell, t_expand *norm)
{
	norm->start = norm->i + 1;
	while (str[norm->start] && (ft_isalnum(str[norm->start])
			|| str[norm->start] == '_'))
		norm->start++;
	norm->key = ft_substr(str, norm->i + 1, norm->start - (norm->i + 1));
	norm->value = get_env_value(norm->key, env_minishell);
	free(norm->key);
	if (!norm->value)
		norm->value = "";
	norm->before = ft_substr(str, 0, norm->i);
	if (!norm->before)
		return (NULL);
	norm->after = ft_strdup(str + norm->start);
	if (!norm->after)
		return (NULL);
	norm->result = ft_strjoin_free(norm->before, norm->value);
	if (!norm->result)
		return (NULL);
	norm->before = norm->result;
	norm->result = ft_strjoin_free(norm->before, norm->after);
	if (!norm->result)
		return (NULL);
	return (free(str), free(norm->after), norm->result);
}

static char	*ft_expand(char *str, char **env_minishell, char in_quote)
{
	t_expand	norm;

	norm.i = 0;
	while (str[norm.i])
	{
		if (str[norm.i] == '$' && (in_quote == '"' || in_quote == 0))
			return (ft_expand_variable(str, env_minishell, &norm));
		norm.i++;
	}
	return (str);
}

char	*ft_expand_var(char *str, char **env_minishell, char q, int *backup)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!q || q == '"'))
			break ;
		i++;
	}
	if (str[i + 1] == '?')
	{
		new_str = ft_expand_status(i, str, backup);
		if (!new_str)
			return (NULL);
		return (new_str);
	}
	else if (ft_isalnum(str[i + 1]))
	{
		new_str = ft_expand(str, env_minishell, q);
		if (!new_str)
			return (NULL);
		return (new_str);
	}
	return (str);
}

char	*ft_process_expansions(char *str, char **env_minishell, char q
	, int *backup)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (!q || q == '"'))
		{
			new_str = ft_expand_var(str, env_minishell, q, backup);
			if (!new_str)
				return (NULL);
			if (new_str != str)
			{
				str = new_str;
				return (str);
			}
		}
		i++;
	}
	return (str);
}

char	*ft_expander(char *str, char **env_minishell, int *backup)
{
	int		i;
	char	q;
	char	*expanded;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"' && !q)
			q = '"';
		else if (str[i] == '\'' && !q)
			q = '\'';
		else if ((str[i] == '"' && q == '"') || (str[i] == '\'' && q == '\''))
			q = 0;
		expanded = ft_process_expansions(str, env_minishell, q, backup);
		if (!expanded)
			return (NULL);
		if (expanded != str)
		{
			str = expanded;
			i = -1;
		}
		i++;
	}
	return (str);
}
