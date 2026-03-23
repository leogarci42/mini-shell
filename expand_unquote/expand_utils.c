/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:01:44 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/10 17:14:58 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expand_build_result(t_expand *norm)
{
	norm->result = ft_strjoin_free(norm->before, norm->value);
	free(norm->value);
	if (!norm->result)
		return (0);
	norm->before = norm->result;
	norm->result = ft_strjoin_free(norm->before, norm->after);
	if (!norm->result)
		return (0);
	return (1);
}

static int	ft_expand_alloc_parts(char *str, t_expand *norm)
{
	norm->before = ft_substr(str, 0, norm->i);
	if (!norm->before)
		return (0);
	if (str[norm->i + 2])
	{
		norm->after = ft_strdup(str + norm->i + 2);
		if (!norm->after)
			return (free(norm->before), 0);
	}
	else
	{
		norm->after = ft_strdup("");
		if (!norm->after)
			return (free(norm->before), 0);
	}
	return (1);
}

static char	*ft_expand_status_core(char *str, t_expand *norm)
{
	if (!ft_expand_alloc_parts(str, norm))
		return (free(norm->value), free(str), NULL);
	if (!ft_expand_build_result(norm))
		return (free(norm->after), free(str), NULL);
	free(norm->after);
	return (free(str), norm->result);
}

char	*ft_expand_status(int i, char *str, int *backup)
{
	t_expand	norm;

	norm.i = i;
	norm.result = NULL;
	norm.value = ft_itoa(backup[EXIT_STATUS]);
	if (!norm.value)
		return (free(str), NULL);
	return (ft_expand_status_core(str, &norm));
}

char	*get_env_value(char *key, char **env_minishell)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env_minishell[i])
	{
		if (ft_strncmp(env_minishell[i], key, key_len) == 0
			&& env_minishell[i][key_len] == '=')
			return (env_minishell[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
