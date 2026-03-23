/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:33:17 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 13:49:37 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenizer	*ft_parsing(char *str, char **envp, int *backup)
{
	t_tokenizer	*head;

	if (str == NULL)
		return (NULL);
	head = ft_tokenizer(str);
	if (!head)
		return (NULL);
	if (ft_automate(head, backup))
	{
		ft_free_token_list(&head);
		return (NULL);
	}
	(void)envp;
	return (head);
}
