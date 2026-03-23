/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:11:41 by gburtin           #+#    #+#             */
/*   Updated: 2025/06/15 13:02:09 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "tokenizer.h"
# include "types.h"
# include <sys/stat.h>

# define READ 0
# define WRITE 1

# define TRUNC 0
# define APPEND 1

typedef struct s_cmd	t_cmd;

typedef struct s_unquote
{
	char				*new_str;
	int					pos;
	int					i;
	int					q;
}						t_unquote;

typedef struct s_pipex
{
	pid_t				*pid;
	int					fd[2];
	int					infile;
	int					outfile;
	int					nb;
}						t_pipex;

typedef struct s_cmd
{
	char				*path;
	char				**args;
	char				*infile;
	char				*outfile;
	int					redir_type;
	t_cmd				*next;
}						t_cmd;

typedef struct s_norm
{
	int			*backup;
	char		**heredoc;
}				t_norm;

/* Execution */
t_boolean				ft_exec_minishell(t_tokenizer **tokens,
							char ***env_minishell, int *backup);
t_boolean				ft_exec_cmd(t_cmd *command, char ***env, int nb_cmd,
							int *backup);
t_boolean				ft_pipe(t_cmd *command, char **envp, int *backup,
							t_pipex pipex);
t_boolean				ft_child_exec(t_cmd *cmd, char **env_minishell,
							int *backup);
t_boolean				ft_redirections(t_cmd *command, int *fd, int infile,
							int outfile);
t_boolean				ft_exec_built_in(t_cmd *cmd, char ***env, int *backup);

/* Command creation */
t_boolean				ft_create_command(t_cmd **command, t_tokenizer *token,
							char **env_minishell, t_norm norm);
char					*ft_expander(char *str, char **env_minishell,
							int *backup);
char					*ft_unquote(char *str);
void					ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_boolean				ft_init_cmd_list(t_cmd **new);
t_boolean				ft_is_command(t_cmd *new, t_tokenizer *tmp,
							char **envp);
t_boolean				ft_fill_new_command_node(t_tokenizer *token,
							char **env_minishell, t_cmd *new, char ***heredoc);
t_boolean				ft_is_args(t_cmd *new, t_tokenizer *tmp);
void					*ft_printf_command(t_cmd *command);

/* Open & Close */
t_boolean				ft_open_files(t_cmd *command, int *infile,
							int *outfile);
t_boolean				ft_close_files(t_cmd *command, int infile, int outfile);
t_boolean				ft_close_backup(int *backup);

/* Built-ins */
t_boolean				ft_is_built_in(char *cmd);
t_boolean				ft_cd(t_cmd *command, char ***envp, int *backup);
t_boolean				ft_chdir_and_env_update(char ***envp, char *dir);
t_boolean				ft_echo(t_cmd *command);
t_boolean				ft_env(t_cmd *command, char **envp, int *backup);
t_boolean				ft_exit(t_cmd **command, char **envp, int *backup);
t_boolean				ft_export(t_cmd *command, char ***envp, int *backup);
t_boolean				ft_pwd(t_cmd *command, int *backup);
t_boolean				ft_unset(t_cmd *command, char ***envp);

/* Environnement */
char					**ft_create_new_envp(char **envp);
char					*ft_get_env_name(char *str);
char					*ft_get_env_value(char *name, char **env);
t_boolean				ft_is_in_env(char **envp, char *name);
t_boolean				ft_update_env(char **envp, char *arg, char *name_arg);
t_boolean				ft_add_env_variable(char ***envp, char *arg);

/* Free functions */
void					ft_free_command_lst(t_cmd **lst);
void					ft_free_token_list(t_tokenizer **lst);
t_cmd					*ft_free_cmd_and_next(t_cmd *lst);
void					ft_free_env_and_cmd_list(t_cmd **command, char **env);

/* Heredoc */
char					**ft_exec_heredoc(t_tokenizer *token, int *backup,
							char **envp);
t_boolean				ft_heredoc(char *delimiter, int *backup, char **envp,
							char *path);
char					*ft_get_heredoc_path(int num);

#endif
