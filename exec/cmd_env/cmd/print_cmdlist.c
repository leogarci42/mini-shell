/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmdlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:41:45 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/06 18:40:23 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*ft_printf_command(t_cmd *command)
{
	t_cmd	*tmp;
	int		i;

	printf("\n");
	if (!command)
		return (printf("Cannot print command list\n"), NULL);
	tmp = command;
	while (tmp)
	{
		printf("> cmd_path: %s\n", tmp->path);
		i = -1;
		if (tmp->args)
			while (tmp->args[++i])
				printf(">> arg_%d: \"%s\"\n", i, tmp->args[i]);
		printf("> infile = %s\n", tmp->infile);
		printf("> outfile = %s\n", tmp->outfile);
		if (tmp->redir_type == TRUNC)
			printf("> redir_type: TRUNC\n");
		if (tmp->redir_type == APPEND)
			printf("> redir_type: APPEND\n");
		printf("> next: %p\n", tmp->next);
		printf("\n");
		tmp = tmp->next;
	}
	return (NULL);
}
