/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:24:10 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/14 19:22:06 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_count_heredoc(t_tokenizer *token)
{
	int			count;
	t_tokenizer	*tmp;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*ft_get_heredoc_path(int num)
{
	char	*path;
	char	*suffix;

	suffix = ft_itoa(num);
	if (!suffix)
		return (NULL);
	path = ft_strjoin(".HEREDOC", suffix);
	if (!path)
		return (free(suffix), NULL);
	free(suffix);
	return (path);
}

char	**ft_create_heredoc_list(int nb)
{
	int		i;
	char	**heredoc;

	i = 0;
	heredoc = ft_calloc(sizeof(char *), (nb + 1));
	if (!heredoc)
		return (NULL);
	while (i < nb)
	{
		heredoc[i] = ft_get_heredoc_path(i);
		if (!heredoc[i])
			return (ft_free_array(heredoc), NULL);
		i++;
	}
	heredoc[i] = NULL;
	return (heredoc);
}

t_boolean	ft_loop_heredoc(t_tokenizer *token, int *backup,
	char **envp, char **heredoc)
{
	int			i;
	t_tokenizer	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			if (ft_heredoc(tmp->next->value, backup,
					envp, heredoc[i]) == FALSE)
			{
				g_status = STATUS_SIGINT_HEREDOC;
				return (FALSE);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

char	**ft_exec_heredoc(t_tokenizer *token, int *backup,
	char **envp)
{
	char		**heredoc;
	int			nb;

	nb = ft_count_heredoc(token);
	if (nb == 0)
	{
		heredoc = malloc(sizeof(char *));
		heredoc[0] = NULL;
		return (heredoc);
	}
	heredoc = ft_create_heredoc_list(nb);
	if (ft_loop_heredoc(token, backup, envp, heredoc))
		return (NULL);
	return (heredoc);
}

// char	**ft_exec_heredoc(t_tokenizer *token, int *backup,
// 	char **envp)
// {
// 	t_tokenizer	*tmp;
// 	char		**heredoc;

// 	tmp = token;
// 	if (ft_count_heredoc(token) == 0)
// 		return (TRUE);
// 	while (tmp)
// 	{
// 		if (tmp->type == HERE_DOC)
// 		{
// 			if (ft_heredoc(tmp->next->value, backup, envp) == FALSE)
// 			{
// 				g_status = STATUS_SIGINT_HEREDOC;
// 				return (FALSE);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (TRUE);
// }