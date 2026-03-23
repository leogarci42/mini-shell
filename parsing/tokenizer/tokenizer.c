/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:30:15 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 13:49:41 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		fprintf(stderr, "tableau: [%d]: %s\n", i, array[i]);
		i++;
	}
}

static t_tokenizer	*ft_tokenize_str(char *str)
{
	char			**ret_val_split;
	t_tokenizer		*head;

	ret_val_split = ft_no_split(str);
	head = NULL;
	if (ft_tokenize_array(ret_val_split, &head))
		return (ft_free_array(ret_val_split), NULL);
	free(ret_val_split);
	classify_cmd_args(head);
	return (head);
}

t_tokenizer	*ft_tokenizer(char *str)
{
	t_tokenizer		*head;

	if (ft_strncmp(str, "", 1) == 0)
		return (NULL);
	head = ft_tokenize_str(str);
	return (head);
}
