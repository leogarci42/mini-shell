/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:57:07 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/14 17:23:04 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_count_args(t_tokenizer *token)
{
	t_tokenizer	*tmp;
	int			nb_args;

	nb_args = 2;
	tmp = token;
	while (tmp && tmp->role == STATE_ARGS)
	{
		nb_args++;
		tmp = tmp->next;
	}
	return (nb_args);
}

t_boolean	ft_add_args(t_tokenizer *token, char **args, char *path, int nb)
{
	int			i;
	t_tokenizer	*tmp;

	args[0] = ft_strdup(path);
	if (!args[0])
		return (FALSE);
	i = 1;
	tmp = token;
	while (i < nb - 1 && tmp)
	{
		args[i] = ft_strdup(tmp->value);
		if (!args[i])
			return (FALSE);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (TRUE);
}

static char	**ft_get_args(t_tokenizer *token, char *path)
{
	int			nb_args;
	char		**args;

	nb_args = ft_count_args(token);
	args = (char **)malloc(sizeof(char *) * (nb_args));
	if (!args)
		return (NULL);
	if (ft_add_args(token, args, path, nb_args) == FALSE)
		return (free(args), NULL);
	return (args);
}

t_boolean	ft_is_args(t_cmd *new, t_tokenizer *tmp)
{
	if (new->args)
		return (TRUE);
	new->args = ft_get_args(tmp, new->path);
	if (!new->args)
		return (FALSE);
	return (TRUE);
}
