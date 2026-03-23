/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:30 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 22:10:50 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_boolean	ft_delete_env_variable(char ***envp, int index_to_delete,
	char *arg, int arg_len)
{
	int	len;

	if (ft_strncmp(arg, "PATH", arg_len))
	{
		len = ft_splitlen(*envp);
		free((*envp)[index_to_delete]);
		while (index_to_delete < len - 1)
		{
			(*envp)[index_to_delete] = (*envp)[index_to_delete + 1];
			index_to_delete++;
		}
		(*envp)[index_to_delete] = NULL;
		return (TRUE);
	}
	return (FALSE);
}

t_boolean	ft_unset(t_cmd *command, char ***envp)
{
	int	i;
	int	j;
	int	arg_len;

	if (!command->args)
		return (TRUE);
	i = 1;
	while (command->args[i])
	{
		j = 0;
		arg_len = ft_strlen(command->args[i]);
		while ((*envp)[j])
		{
			if (!ft_strncmp(command->args[i], (*envp)[j], arg_len)
				&& ((*envp)[j][arg_len] == '=' || (*envp)[j][arg_len] == '\0'))
			{
				if (ft_delete_env_variable(envp, j, command->args[i], arg_len))
					j++;
				continue ;
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
