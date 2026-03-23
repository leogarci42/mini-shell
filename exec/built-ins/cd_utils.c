/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:58:02 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/15 14:27:49 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_boolean	ft_oldpwd(char ***envp, char *cur_pwd)
{
	char	*join;

	if (ft_is_in_env(*envp, "OLDPWD") == TRUE)
	{
		join = ft_strjoin("OLDPWD=", cur_pwd);
		if (!join)
			return (FALSE);
		if (ft_update_env(*envp, join, "OLDPWD") == FALSE)
			return (free(join), FALSE);
	}
	else
	{
		join = ft_strjoin("OLDPWD=", cur_pwd);
		if (!join)
			return (FALSE);
		if (ft_add_env_variable(envp, join))
			return (free(join), FALSE);
	}
	free(join);
	return (TRUE);
}

static t_boolean	ft_get_pwd(char ***envp)
{
	char	*pwd;
	char	*join;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd"), FALSE);
	if (ft_is_in_env(*envp, "PWD") == TRUE)
	{
		join = ft_strjoin("PWD=", pwd);
		if (!join)
			return (free(pwd), FALSE);
		if (ft_update_env(*envp, join, "PWD") == FALSE)
			return (free(join), free(pwd), FALSE);
	}
	else
	{
		join = ft_strjoin("PWD=", pwd);
		if (!join)
			return (free(pwd), FALSE);
		if (ft_add_env_variable(envp, join))
			return (free(join), free(pwd), FALSE);
	}
	free(join);
	free(pwd);
	return (TRUE);
}

t_boolean	ft_chdir_and_env_update(char ***envp, char *dir)
{
	char	*cur_pwd;

	cur_pwd = ft_get_env_value("PWD", *envp);
	if (!cur_pwd)
	{
		cur_pwd = getcwd(NULL, 0);
		if (!cur_pwd)
			return (perror("getcwd"), FALSE);
	}
	if (chdir(dir))
		return (free(cur_pwd), perror("chdir"), FALSE);
	if (ft_oldpwd(envp, cur_pwd) == FALSE)
		return (free(cur_pwd), FALSE);
	if (ft_get_pwd(envp) == FALSE)
		return (free(cur_pwd), FALSE);
	free(cur_pwd);
	return (TRUE);
}
