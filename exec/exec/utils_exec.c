/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:54:07 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/11 14:36:31 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (TRUE);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (TRUE);
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (TRUE);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (TRUE);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (TRUE);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (TRUE);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (TRUE);
	else
		return (FALSE);
}

t_boolean	ft_open_files(t_cmd *cmd, int *infile, int *outfile)
{
	if (cmd->infile)
	{
		if (ft_strlen(cmd->infile) == 0)
			return (FALSE);
		*infile = open(cmd->infile, O_RDONLY);
	}
	if (cmd->outfile)
	{
		if (ft_strlen(cmd->outfile) == 0)
			return (FALSE);
		if (cmd->redir_type == TRUNC)
			*outfile = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			*outfile = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (*infile == -1 || *outfile == -1)
		return (perror("open"), FALSE);
	return (TRUE);
}

t_boolean	ft_close_files(t_cmd *command, int infile, int outfile)
{
	if (command->infile)
	{
		if (close(infile) == -1)
			return (perror("close"), FALSE);
	}
	if (command->outfile)
	{
		if (close(outfile) == -1)
			return (perror("close"), FALSE);
	}
	return (TRUE);
}

t_boolean	ft_close_backup(int *backup)
{
	if (close(backup[STDIN_FILENO]) < 0)
		return (FALSE);
	if (close(backup[STDOUT_FILENO]) < 0)
		return (FALSE);
	return (TRUE);
}
