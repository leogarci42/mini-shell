/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:23:55 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/09 16:57:09 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_free_command_lst(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->path);
		free(current->infile);
		free(current->outfile);
		ft_free_array(current->args);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_free_env_and_cmd_list(t_cmd **command, char **env)
{
	ft_free_array(env);
	ft_free_command_lst(command);
}

void	ft_free_token_list(t_tokenizer **lst)
{
	t_tokenizer	*current;
	t_tokenizer	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}

t_cmd	*ft_free_cmd_and_next(t_cmd *lst)
{
	t_cmd	*next;

	if (!lst)
		return (NULL);
	next = lst->next;
	if (lst->path)
		free(lst->path);
	if (lst->infile)
		free(lst->infile);
	if (lst->outfile)
		free(lst->outfile);
	if (lst->args)
		ft_free_array(lst->args);
	free(lst);
	return (next);
}
