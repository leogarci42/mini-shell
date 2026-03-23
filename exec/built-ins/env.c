/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:04:42 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 21:36:21 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env with no options or arguments

#include "exec.h"

t_boolean	ft_env(t_cmd *command, char **envp, int *backup)
{
	int	i;

	if (command->args)
	{
		if (ft_splitlen(command->args) != 1)
		{
			backup[EXIT_STATUS] = 1;
			return (printf("env: too many arguments\n"), FALSE);
		}
	}
	i = 0;
	while (envp[i])
	{
		if (!envp[i])
		{
			if (printf("Warning: envp[%d] is NULL\n", i) < 0)
				return (perror("printf"), FALSE);
			break ;
		}
		if (ft_strchr(envp[i], '='))
			if (printf("%s\n", envp[i]) < 0)
				return (perror("printf"), FALSE);
		i++;
	}
	return (TRUE);
}
