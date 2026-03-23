/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:14:43 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 15:10:15 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "./../all_libft/all_libft.h"
# include "types.h"
# include <stdio.h>
# include <stdlib.h>

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEN,
	HERE_DOC,
	AND,
	OR,
	PARENT_IN,
	PARENT_OUT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NOTHING,
}						t_token;

typedef enum e_role
{
	NONE,
	STATE_CMD,
	STATE_ARGS,
	STATE_REDIR_IN,
	STATE_REDIR_OUT,
	STATE_REDIR_IN_TARGET,
	STATE_REDIR_OUT_TARGET,
	STATE_HEREDOC,
	STATE_HEREDOC_DOC,
	STATE_APPEN,
	STATE_APPEN_TARGET,
	STATE_PARENT_IN,
	STATE_PARENT_OUT,
	STATE_PIPE,
	STATE_AND,
	STATE_OR,
}						t_role;

typedef struct s_tokenizer
{
	t_token				type;
	t_role				role;
	char				*value;
	struct s_tokenizer	*next;
}						t_tokenizer;

typedef struct s_join_state
{
	char				*joined;
	int					k;
	int					in_quote;
	char				quote_char;
}						t_join_state;

typedef struct s_count_join_words
{
	int					i;
	int					count;
	int					in_quote;
	char				quote_char;
}						t_count_join_words;

typedef struct s_gburtin
{
	t_tokenizer			*token;
	char				**envp;
}						t_gburtin;

void					ft_join_quotes_in_split(char ***split_ptr);

/*							quotes utils						*/

void					add_word_to_result(char **result, int *k, char *curr);
int						append_to_joined_and_check_close(char **joined,
							char *curr);
int						check_and_close_quote(char *curr, char **result,
							t_join_state *norm);
int						init_quote_join(char **joined, char *curr,
							char *quote_char);
int						is_quote(char c);
void					ft_process_quote_joining(char **split, char **result,
							t_join_state *st);
void					process_start_of_quote(char *current, char **result,
							t_join_state *st);
void					handle_closed_quote(char *current, char **result,
							t_join_state *st, char *quote_pos);
void					process_inside_quote(char *current, char **result,
							t_join_state *st);
void					handle_unfinished_quote(char **result,
							t_join_state *st);
int						append_partial_to_joined(t_join_state *st,
							const char *src, size_t len);

/*							tokenize utils							*/

t_boolean				*init_t_tokenizer(t_tokenizer **token);
t_boolean				ft_tokenize_array(char **to_tokenize,
							t_tokenizer **token);
t_boolean				handle_pipe(char **to_tokenize, t_tokenizer **token,
							int i);
t_boolean				handle_redirects(char **to_tokenize,
							t_tokenizer **token, int i);
t_boolean				handle_double_ops(char **to_tokenize,
							t_tokenizer **token, int i);
t_boolean				handle_parentheses(char **to_tokenize,
							t_tokenizer **token, int i);
t_boolean				handle_quotes(char **to_tokenize, t_tokenizer **token,
							int i);
t_tokenizer				*ft_t_tokenizer_new(char *to_tokenize, uint8_t i);
t_boolean				ft_t_tokenizer_add_back(t_tokenizer **token,
							t_tokenizer *new);
void					print_token_list(t_tokenizer *head);
void					ft_print_array(char **array);
char					**ft_no_split(char *str);
char					*ft_copy_meta_char(char *str, int i, int len);

/*								define role							*/

void					classify_cmd_args(t_tokenizer *head);
char					**split_quote_aware(char *str, char *charset);

#endif
