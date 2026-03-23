/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:26:13 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/10 20:10:06 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**ft_if_empty_env(void)
{
	char	*pwd;
	char	**new;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	pwd = ft_strjoin("PWD=", pwd);
	if (!pwd)
		return (free(pwd), NULL);
	new = malloc(5 * sizeof(char *));
	if (!new)
		return (free(pwd), NULL);
	new[0] = ft_strdup(pwd);
	new[1] = ft_strdup("SHLVL=1");
	new[2] = ft_strdup("OLDPWD=");
	new[3] = ft_strdup("PATH=/usr/sbin:/usr/bin:/sbin:/bin");
	if (!new[0] || !new[1] || !new[2] || !new[3])
		return (free(new), free(pwd), NULL);
	new[4] = NULL;
	free(pwd);
	return (new);
}

t_boolean	ft_get_new_envp(char **envp, char **new)
{
	int		i;
	char	*itoa;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			itoa = ft_itoa(envp[i][6] - '0' + 1);
			new[i] = ft_strjoin("SHLVL=", itoa);
			if (!new[i])
				return (free(new), free(itoa), FALSE);
			free(itoa);
		}
		else
		{
			new[i] = ft_strdup(envp[i]);
			if (!new[i])
				return (free(new), FALSE);
		}
		i++;
	}
	new[i] = NULL;
	return (TRUE);
}

char	**ft_create_new_envp(char **envp)
{
	char	**new;

	if (envp[0] == NULL)
		new = ft_if_empty_env();
	else
	{
		new = malloc((ft_splitlen(envp) + 1) * sizeof(char *));
		if (!new)
			return (NULL);
		if (ft_get_new_envp(envp, new) == FALSE)
			return (NULL);
	}
	return (new);
}
