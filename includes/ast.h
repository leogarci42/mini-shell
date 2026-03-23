/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:07:06 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/06 20:57:45 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokenizer.h"
# include "types.h"

typedef enum e_ast_type
{
	PIPE,
	AND,
	OR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEN,
	REDIR_HEREDOC,
	CMD,
}					t_ast_type;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;
	t_token			type;
}					t_ast;

#endif
