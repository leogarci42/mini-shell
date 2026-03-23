/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:28:23 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 11:36:23 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../all_libft/all_libft.h"
# include "exec.h"
# include "ft_signal.h"
# include "tokenizer.h"
# include "types.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define DARK_GREEN "\001\033[38;5;22m\002"
# define RESET "\001\033[0m\002"
# define STATUS_OK 0
# define STATUS_SIGINT_MAIN 1
# define STATUS_SIGINT_HEREDOC 2
# define STATUS_EXIT_CHILD 3
# define EXIT_STATUS 2
# define STATUS_SIGINT_EXEC 4
# define STATUS_EXEC_OK 5
# define ST "\nwarning: here-document delimited by end-of-file (wanted '%s')\n"
# define SA "syntax error near unexpected token `%s'\n"

typedef struct s_expand
{
	int		i;
	int		start;
	char	*key;
	char	*value;
	char	*before;
	char	*after;
	char	*result;
}			t_expand;

t_tokenizer	*ft_parsing(char *str, char **envp, int *backup);
t_tokenizer	*ft_tokenizer(char *str);
void		print_token_list(t_tokenizer *head);
t_boolean	ft_has_closing_quote(char *str, int start, char quote);

/*			readline_history_utils			*/

void		clear_history_commands(void);
void		add_command_to_history(const char *command);
char		*ft_preprocess_cmd_string(char *input);

/*					automate utils			*/

t_boolean	ft_automate(t_tokenizer *head, int *backup);

/*					signal					*/

void		setup_signals_main(void);
void		setup_signals_child(void);
void		setup_heredoc_signals(void);

/*					expand					*/

char		*ft_expand_status(int i, char *str, int *backup);
char		*get_env_value(char *key, char **env_minishell);

/*					main utils				*/

void		ft_run_minishell_loop(char **env_minishell, int *backup);
char		*ft_get_prompt_safe(void);
int			ft_too_many_args(void);
void		ft_backup_io(int backup[3]);
t_boolean	ft_check_isspace(char *str);
void		ft_restore_io(int *backup);
int			ft_handle_null_input(char *str, char *prompt,
				char **env_minishell, int *backup);
void		ft_continue_empty(char *prompt, char *str);
void		ft_handle_no_tokens(char *cstr, char *prompt, int *backup);
void		ft_handle_clear_history(char *cstr);
char		*get_prompt(void);
char		*ft_get_prompt_safe(void);

#endif
