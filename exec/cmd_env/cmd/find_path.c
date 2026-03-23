/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:08:55 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/11 16:39:53 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*ft_check_exec_path(char **split, char *prefixed_cmd)
{
	char	**tmp;
	char	*path;

	tmp = split;
	while (*tmp)
	{
		path = ft_strjoin(*tmp, prefixed_cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		tmp++;
	}
	return (NULL);
}

char	*ft_find_exec_path(char *cmd, char **envp)
{
	char	*sub;
	char	*path;
	char	**split;
	char	*prefixed_cmd;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (ft_is_built_in(cmd) == TRUE)
		return (ft_strdup(cmd));
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	sub = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	split = ft_split(sub, ':');
	free(sub);
	if (!sub || !split)
		return (NULL);
	prefixed_cmd = ft_strjoin("/", cmd);
	if (!prefixed_cmd)
		return (NULL);
	path = ft_check_exec_path(split, prefixed_cmd);
	if (path)
		return (ft_free_array(split), free(prefixed_cmd), path);
	return (ft_free_array(split), free(prefixed_cmd), NULL);
}

t_boolean	ft_is_command(t_cmd *new, t_tokenizer *tmp, char **envp)
{
	new->path = ft_find_exec_path(tmp->value, envp);
	if (!new->path)
	{
		new->path = ft_strdup(tmp->value);
		if (!new->path)
			return (FALSE);
	}
	return (TRUE);
}
