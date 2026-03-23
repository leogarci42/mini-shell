/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:07:49 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/09 18:28:52 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pwd with no options

#include "exec.h"

t_boolean	ft_pwd(t_cmd *command, int *backup)
{
	char	*pwd;

	if (command->args)
	{
		if (ft_splitlen(command->args) > 1)
		{
			backup[EXIT_STATUS] = 1;
			return (printf("pwd: too many arguments\n"), FALSE);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), FALSE);
	if (printf("%s\n", pwd) < 0)
		return (FALSE);
	free(pwd);
	return (TRUE);
}
