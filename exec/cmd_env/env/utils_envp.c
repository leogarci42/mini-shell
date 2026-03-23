/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:35:27 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/11 14:12:43 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_add_env_variable(char ***envp, char *arg)
{
	char	**new;
	int		i;
	int		envp_len;

	envp_len = ft_splitlen(*envp);
	new = malloc(sizeof(char *) * (envp_len + 2));
	if (!new)
		return (FALSE);
	i = 0;
	while ((*envp)[i])
	{
		new[i] = ft_strdup((*envp)[i]);
		if (!new[i])
			return (free(new), FALSE);
		i++;
	}
	new[i] = ft_strdup(arg);
	if (!new)
		return (free(new), FALSE);
	new[i + 1] = NULL;
	ft_free_array(*envp);
	*envp = new;
	return (TRUE);
}

t_boolean	ft_update_env(char **envp, char *arg, char *name_arg)
{
	char	*name_env;
	int		i;
	size_t	len_name_arg;

	len_name_arg = ft_strlen(name_arg);
	i = 0;
	while (envp[i])
	{
		name_env = ft_get_env_name(envp[i]);
		if (!name_env)
			return (FALSE);
		if (!ft_strncmp(name_env, name_arg, len_name_arg)
			&& len_name_arg == ft_strlen(name_env))
		{
			free(envp[i]);
			free(name_env);
			envp[i] = ft_strdup(arg);
			if (!envp[i])
				return (FALSE);
			return (TRUE);
		}
		i++;
		free(name_env);
	}
	return (FALSE);
}

char	*ft_get_env_name(char *str)
{
	int		len;
	char	*tmp;
	char	*name;

	tmp = str;
	len = 0;
	while (tmp[len] && tmp[len] != '=')
		len++;
	name = ft_substr(str, 0, len);
	if (!name)
		return (NULL);
	return (name);
}

t_boolean	ft_is_in_env(char **envp, char *name)
{
	int		i;
	size_t	len;
	char	*variable;

	i = 0;
	while (envp[i])
	{
		variable = ft_get_env_name(envp[i]);
		len = ft_strlen(variable);
		if (!ft_strncmp(variable, name, len) && len == ft_strlen(name))
		{
			free(variable);
			return (TRUE);
		}
		i++;
		free(variable);
	}
	return (FALSE);
}

char	*ft_get_env_value(char *name, char **env)
{
	size_t	len;
	int		i;
	char	*value;
	char	*var;

	value = NULL;
	if (ft_is_in_env(env, name) == FALSE)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		var = ft_get_env_name(env[i]);
		if (!ft_strncmp(name, env[i], len) && len == ft_strlen(var))
		{
			value = ft_substr(&env[i][len], 1, (ft_strlen(env[i]) - len));
			if (!value)
				return (free(var), NULL);
		}
		free(var);
		i++;
	}
	return (value);
}
