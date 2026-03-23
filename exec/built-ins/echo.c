/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:23 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/13 21:50:49 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// echo with option -n

#include "exec.h"

static t_boolean	ft_is_valid_option(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	if (str[0] != '-')
		return (FALSE);
	if (str[1] == '\0')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*ft_get_to_print(t_cmd *command, int i)
{
	char	*to_print;

	to_print = ft_strdup("");
	if (!to_print)
		return (NULL);
	while (command->args[i])
	{
		to_print = ft_strjoin_free(to_print, command->args[i]);
		if (!to_print)
			return (NULL);
		if (command->args[i + 1])
		{
			to_print = ft_strjoin_free(to_print, " ");
			if (!to_print)
				return (NULL);
		}
		i++;
	}
	return (to_print);
}

t_boolean	ft_print_echo(char *to_print)
{
	if (!to_print)
		return (FALSE);
	else
		if (printf("%s", to_print) < 0)
			return (perror("printf"), FALSE);
	return (TRUE);
}

t_boolean	ft_echo(t_cmd *command)
{
	char		*to_print;
	int			i;
	t_boolean	flag_option;

	i = 0;
	flag_option = FALSE;
	if (!command->args)
	{
		if (printf("\n") < 0)
			return (perror("printf"), FALSE);
		return (TRUE);
	}
	while (ft_is_valid_option(command->args[++i]) == TRUE)
		flag_option = TRUE;
	if (command->args[i])
	{
		to_print = ft_get_to_print(command, i);
		if (ft_print_echo(to_print) == FALSE)
			return (FALSE);
		free(to_print);
	}
	if (flag_option == FALSE)
		if (printf("\n") < 0)
			return (perror("printf"), FALSE);
	return (TRUE);
}
