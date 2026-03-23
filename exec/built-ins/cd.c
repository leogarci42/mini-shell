/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:18 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/14 18:51:47 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cd with only a relative or absolute path

#include "exec.h"

t_boolean	ft_cd_previous(char ***envp)
{
	char	*oldpwd;

	oldpwd = ft_get_env_value("OLDPWD", *envp);
	if (!oldpwd)
		return (printf("OLDPWD is not set\n"), FALSE);
	if (ft_chdir_and_env_update(envp, oldpwd) == FALSE)
		return (free(oldpwd), FALSE);
	free(oldpwd);
	return (TRUE);
}

t_boolean	ft_cd_with_args(t_cmd *command, char ***envp, char *home)
{
	if (!ft_strncmp(command->args[1], "-", 1)
		&& ft_strlen(command->args[1]) == 1)
	{
		if (ft_cd_previous(envp) == FALSE)
			return (FALSE);
	}
	else if (!ft_strncmp(command->args[1], "~", 1)
		&& ft_strlen(command->args[1]) == 1)
	{
		if (!home)
			return (printf("HOME is not set\n"), FALSE);
		if (ft_chdir_and_env_update(envp, home) == FALSE)
			return (FALSE);
	}
	else
	{
		if (ft_chdir_and_env_update(envp, command->args[1]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

t_boolean	ft_cd(t_cmd *command, char ***envp, int *backup)
{
	char	*home;

	home = ft_get_env_value("HOME", *envp);
	if (!command->args)
	{
		if (!home)
			return (printf("HOME is not set\n"), FALSE);
		if (ft_chdir_and_env_update(envp, home) == FALSE)
			return (free(home), FALSE);
		free(home);
	}
	else if (ft_splitlen(command->args) > 2)
	{
		backup[EXIT_STATUS] = 1;
		return (free(home), printf("cd: too many arguments\n"), FALSE);
	}
	else
	{
		if (ft_cd_with_args(command, envp, home) == FALSE)
			return (free(home), FALSE);
		free(home);
	}
	return (TRUE);
}
