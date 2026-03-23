/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:04:25 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 21:40:18 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_child_process(t_pipex pipex, t_cmd *cmd, char **envp,
	int *backup)
{
	setup_signals_child();
	if (ft_redirections(cmd, pipex.fd, pipex.infile, pipex.outfile) == FALSE)
		return (FALSE);
	if (close(pipex.fd[WRITE]) == -1 || close(pipex.fd[READ]) == -1)
		return (FALSE);
	if (ft_child_exec(cmd, envp, backup) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_boolean	ft_parent_process(t_pipex pipex, t_cmd *tmp, int *backup)
{
	(void)backup;
	if (tmp->next)
		if (dup2(pipex.fd[READ], STDIN_FILENO) == -1)
			return (perror("dup"), FALSE);
	if (close(pipex.fd[WRITE]) == -1 || close(pipex.fd[READ]) == -1)
		return (perror("close"), FALSE);
	if (ft_close_files(tmp, pipex.infile, pipex.outfile) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_boolean	ft_pipe(t_cmd *command, char **envp, int *backup,
	t_pipex pipex)
{
	t_boolean	files;

	files = ft_open_files(command, &pipex.infile, &pipex.outfile);
	if (pipe(pipex.fd) == -1)
		return (perror("pipe"), FALSE);
	g_status = STATUS_EXEC_OK;
	pipex.pid[pipex.nb - 1] = fork();
	if (pipex.pid[pipex.nb - 1] == -1)
		return (perror("fork"), FALSE);
	else if (pipex.pid[pipex.nb - 1] == 0)
	{
		free(pipex.pid);
		if (files == TRUE)
			ft_child_process(pipex, command, envp, backup);
		if (close(pipex.fd[WRITE]) == -1 || close(pipex.fd[READ]) == -1)
			return (FALSE);
		ft_free_env_and_cmd_list(&command, envp);
		if (ft_close_backup(backup) == FALSE)
			return (FALSE);
		backup[EXIT_STATUS] = 1;
		exit(backup[EXIT_STATUS]);
	}
	if (ft_parent_process(pipex, command, backup) == FALSE)
		return (FALSE);
	return (TRUE);
}
