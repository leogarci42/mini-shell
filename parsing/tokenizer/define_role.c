/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_role.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 03:37:46 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/08 18:16:29 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	process_pipe_logical(t_tokenizer *curr, int *expect_cmd)
{
	if (curr->type == PIPE || curr->type == AND || curr->type == OR)
		*expect_cmd = 1;
	if (curr->type == PIPE)
		curr->role = STATE_PIPE;
	if (curr->type == AND)
		curr->role = STATE_AND;
	if (curr->type == OR)
		curr->role = STATE_OR;
}

static void	process_word_redir_part2(t_tokenizer *curr, int *expect_cmd)
{
	if (curr->type == REDIR_OUT && curr->next)
	{
		curr->role = STATE_REDIR_OUT;
		curr->next->role = STATE_REDIR_OUT_TARGET;
		curr = curr->next;
	}
	if ((curr->type == WORD || curr->type == SINGLE_QUOTE
			|| curr->type == DOUBLE_QUOTE) && curr->role == NONE)
	{
		if (*expect_cmd)
		{
			curr->role = STATE_CMD;
			*expect_cmd = 0;
		}
		else if (curr->role == NONE)
			curr->role = STATE_ARGS;
	}
	else if (curr->type == REDIR_APPEN || curr->type == HERE_DOC)
		curr = curr->next;
}

static void	process_word_redir(t_tokenizer *curr, int *expect_cmd)
{
	if (curr->type == REDIR_APPEN && curr->next)
	{
		curr->role = STATE_APPEN;
		curr->next->role = STATE_APPEN_TARGET;
		curr = curr->next;
	}
	if (curr->type == HERE_DOC && curr->next)
	{
		curr->role = STATE_HEREDOC;
		curr->next->role = STATE_HEREDOC_DOC;
		curr = curr->next;
	}
	if (curr->type == REDIR_IN && curr->next)
	{
		curr->role = STATE_REDIR_IN;
		curr->next->role = STATE_REDIR_IN_TARGET;
		curr = curr->next;
	}
	process_word_redir_part2(curr, expect_cmd);
}

void	classify_cmd_args(t_tokenizer *head)
{
	t_tokenizer	*curr;
	int			expect_cmd;

	expect_cmd = 1;
	curr = head;
	while (curr)
	{
		process_pipe_logical(curr, &expect_cmd);
		process_word_redir(curr, &expect_cmd);
		curr = curr->next;
	}
}
