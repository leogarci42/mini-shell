/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:28 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 15:40:32 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// export with no options
// export — set the export attribute for variables
// export name[=word]...

#include "exec.h"

static t_boolean	ft_check_valid_arg(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (FALSE);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_boolean	ft_update_or_add(char ***envp, char *arg, char *name_arg)
{
	if (!name_arg)
		return (FALSE);
	if (ft_is_in_env(*envp, name_arg) == TRUE)
	{
		if (ft_update_env(*envp, arg, name_arg) == FALSE)
			return (free(name_arg), FALSE);
	}
	else
	{
		if (ft_add_env_variable(envp, arg) == FALSE)
			return (free(name_arg), FALSE);
	}
	return (TRUE);
}

t_boolean	ft_export(t_cmd *cmd, char ***envp, int *backup)
{
	int		i;
	int		args_len;
	char	*name;

	if (!cmd->args)
		return (TRUE);
	args_len = ft_splitlen(cmd->args);
	i = 0;
	while (++i < args_len)
	{
		if (ft_check_valid_arg(cmd->args[i]) == FALSE)
		{
			backup[EXIT_STATUS] = 1;
			return (printf("export: %s: not a valid identifier\n",
					cmd->args[i]), FALSE);
		}
		else
		{
			name = ft_get_env_name(cmd->args[i]);
			if (ft_update_or_add(envp, cmd->args[i], name) == FALSE)
				return (FALSE);
			free(name);
		}
	}
	return (TRUE);
}
