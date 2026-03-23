/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:52:30 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/11 14:28:07 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_boolean	ft_redirections(t_cmd *command, int *fd, int infile, int outfile)
{
	if (infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			return (perror("dup2"), FALSE);
		if (close(infile) == -1)
			return (perror("close"), FALSE);
	}
	if (outfile != 1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (perror("dup2"), FALSE);
		if (close(outfile) == -1)
			return (perror("close"), FALSE);
	}
	else if (command->next)
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			return (perror("dup2"), FALSE);
	}
	return (TRUE);
}
