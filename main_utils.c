/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:04:06 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 17:21:48 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_io(int *backup)
{
	dup2(backup[STDIN_FILENO], STDIN_FILENO);
	dup2(backup[STDOUT_FILENO], STDOUT_FILENO);
}

int	ft_handle_null_input(char *str, char *prompt,
	char **env_minishell, int *backup)
{
	if (str == NULL)
	{
		free(prompt);
		ft_free_array(env_minishell);
		ft_close_backup(backup);
		write(1, "exit\n", 5);
		g_status = errno;
		exit(g_status);
	}
	return (1);
}

void	ft_continue_empty(char *prompt, char *str)
{
	free(prompt);
	free(str);
	g_status = STATUS_OK;
}

void	ft_handle_no_tokens(char *cstr, char *prompt, int *backup)
{
	(void)backup;
	free(prompt);
	free(cstr);
}

void	ft_handle_clear_history(char *cstr)
{
	if (ft_strncmp(cstr, "clear_history", 14) == 0)
	{
		clear_history_commands();
		printf("Command history cleared.\n");
	}
}
