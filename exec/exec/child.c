/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:20:39 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 20:53:57 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_child_built_in(t_cmd *cmd, char **env_minishell, int *backup)
{
	if (ft_exec_built_in(cmd, &env_minishell, backup) == FALSE)
		return (FALSE);
	ft_free_env_and_cmd_list(&cmd, env_minishell);
	if (ft_close_backup(backup) == FALSE)
		return (FALSE);
	exit(backup[EXIT_STATUS]);
	return (TRUE);
}

t_boolean	ft_check_command(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) != 0)
	{
		write(2, path, ft_strlen(path));
		ft_putstr_fd(": command not found\n", 2);
		return (FALSE);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (FALSE);
	}
	if (!(sb.st_mode & S_IXUSR))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

t_boolean	ft_child_extern(t_cmd *cmd, char **env_minishell, int *backup)
{
	if (ft_close_backup(backup) == FALSE)
		return (FALSE);
	if (ft_check_command(cmd->path) == FALSE)
	{
		ft_free_env_and_cmd_list(&cmd, env_minishell);
		backup[EXIT_STATUS] = 127;
		exit(backup[EXIT_STATUS]);
	}
	if (execve(cmd->path, cmd->args, env_minishell) == -1)
	{
		perror("execve");
		ft_free_env_and_cmd_list(&cmd, env_minishell);
		backup[EXIT_STATUS] = 127;
		exit(backup[EXIT_STATUS]);
	}
	return (TRUE);
}

t_boolean	ft_child_exec(t_cmd *cmd, char **env_minishell,	int *backup)
{
	if (!cmd->path)
	{
		ft_free_env_and_cmd_list(&cmd, env_minishell);
		ft_close_backup(backup);
		exit(backup[EXIT_STATUS]);
	}
	else if (ft_is_built_in(cmd->path) == TRUE)
	{
		if (ft_child_built_in(cmd, env_minishell, backup) == FALSE)
			return (FALSE);
	}
	else
	{
		if (ft_child_extern(cmd, env_minishell, backup) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
