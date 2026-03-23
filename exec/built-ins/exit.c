/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:20:17 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 18:34:52 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exit with no options

#include "exec.h"

static t_boolean	ft_is_correct_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_boolean	ft_exit_norm(char *str, int *backup)
{
	if (ft_is_correct_arg(str))
	{
		backup[EXIT_STATUS] = 2;
		printf("exit\nexit: %s: numeric argument required\n", str);
		return (TRUE);
	}
	else
	{
		backup[EXIT_STATUS] = 1;
		return (printf("exit\nexit: too many arguments\n"), FALSE);
	}
}

t_boolean	ft_exit(t_cmd **command, char **envp, int *backup)
{
	int	len;

	if ((*command)->args)
	{
		len = ft_splitlen((*command)->args);
		if (len > 2)
		{
			if (ft_exit_norm((*command)->args[1], backup))
				return (FALSE);
		}
		if (len == 2 && ft_is_correct_arg((*command)->args[1]) == FALSE)
			return (FALSE);
		if (len == 2)
			backup[EXIT_STATUS] = ft_atoi((*command)->args[1]);
	}
	else
	{
		if (g_status != STATUS_EXEC_OK && g_status != STATUS_EXIT_CHILD)
			printf("exit\n");
	}
	ft_free_env_and_cmd_list(command, envp);
	ft_close_backup(backup);
	exit(backup[EXIT_STATUS]);
	return (FALSE);
}
