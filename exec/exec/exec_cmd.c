/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:47:18 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 21:41:45 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_exec_built_in(t_cmd *cmd, char ***env, int *backup)
{
	if (!ft_strncmp(cmd->path, "exit", 4) && ft_strlen(cmd->path) == 4)
		if (ft_exit(&cmd, *env, backup) == FALSE)
			return (FALSE);
	backup[EXIT_STATUS] = 0;
	if (!ft_strncmp(cmd->path, "pwd", 3) && ft_strlen(cmd->path) == 3)
		if (ft_pwd(cmd, backup) == FALSE)
			return (FALSE);
	if (!ft_strncmp(cmd->path, "env", 3) && ft_strlen(cmd->path) == 3)
		if (ft_env(cmd, *env, backup) == FALSE)
			return (FALSE);
	if (!ft_strncmp(cmd->path, "echo", 4) && ft_strlen(cmd->path) == 4)
		if (ft_echo(cmd) == FALSE)
			return (FALSE);
	if (!ft_strncmp(cmd->path, "cd", 2) && ft_strlen(cmd->path) == 2)
		if (ft_cd(cmd, env, backup) == FALSE)
			return (FALSE);
	if (!ft_strncmp(cmd->path, "export", 6) && ft_strlen(cmd->path) == 6)
		if (ft_export(cmd, env, backup) == FALSE)
			return (FALSE);
	if (!ft_strncmp(cmd->path, "unset", 5) && ft_strlen(cmd->path) == 5)
		if (ft_unset(cmd, env) == FALSE)
			return (FALSE);
	return (TRUE);
}

t_boolean	ft_exec_one_command(t_cmd *command, char ***env_minishell,
	int *backup)
{
	t_pipex	pipex;

	pipex.infile = STDIN_FILENO;
	pipex.outfile = STDOUT_FILENO;
	if (ft_open_files(command, &pipex.infile, &pipex.outfile) == FALSE)
	{
		backup[EXIT_STATUS] = 1;
		return (ft_free_command_lst(&command), TRUE);
	}
	if (ft_redirections(command, pipex.fd, pipex.infile,
			pipex.outfile) == FALSE)
		return (FALSE);
	if (ft_exec_built_in(command, env_minishell, backup) == FALSE)
		return (ft_free_command_lst(&command), FALSE);
	ft_free_command_lst(&command);
	return (TRUE);
}

t_boolean	ft_pipex_init(t_pipex *pipex, int nb_cmd)
{
	pipex->infile = STDIN_FILENO;
	pipex->outfile = STDOUT_FILENO;
	pipex->pid = malloc(nb_cmd * sizeof(pid_t));
	if (!pipex->pid)
		return (FALSE);
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
	pipex->nb = nb_cmd;
	return (TRUE);
}

void	ft_wait_children(t_pipex pipex, int nb_cmd, int *backup)
{
	int	w_status;

	w_status = 0;
	while (nb_cmd > 0)
	{
		waitpid(pipex.pid[nb_cmd - 1], &w_status, 0);
		if (WIFEXITED(w_status))
			backup[EXIT_STATUS] = WEXITSTATUS(w_status);
		else
			backup[EXIT_STATUS] = 128 + WTERMSIG(w_status);
		nb_cmd--;
	}
}

t_boolean	ft_exec_cmd(t_cmd *command, char ***env_minishell, int nb_cmd,
	int *backup)
{
	t_pipex	pipex;

	if (nb_cmd == 1 && command->path)
	{
		if (ft_is_built_in(command->path) == TRUE)
		{
			if (ft_exec_one_command(command, env_minishell, backup) == FALSE)
				return (FALSE);
			return (TRUE);
		}
	}
	if (ft_pipex_init(&pipex, nb_cmd) == FALSE)
		return (FALSE);
	while (pipex.nb > 0)
	{
		if (ft_pipe(command, *env_minishell, backup, pipex)
			== FALSE)
			return (free(pipex.pid), FALSE);
		command = ft_free_cmd_and_next(command);
		pipex.nb--;
	}
	ft_wait_children(pipex, nb_cmd, backup);
	free(pipex.pid);
	return (TRUE);
}
