/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:59:27 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/14 20:59:39 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char		cwd[1024];
	char		*prompt;
	size_t		size;
	const char	*sep;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	sep = "$ ";
	size = ft_strlen(DARK_GREEN) + ft_strlen(cwd)
		+ ft_strlen(sep) + ft_strlen(RESET) + 1;
	prompt = malloc(size);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, DARK_GREEN, size);
	ft_strlcat(prompt, cwd, size);
	ft_strlcat(prompt, sep, size);
	ft_strlcat(prompt, RESET, size);
	return (prompt);
}

char	*ft_get_prompt_safe(void)
{
	char	*prompt;

	prompt = get_prompt();
	if (!prompt)
		prompt = strdup("Minishell> ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env_minishell;
	int		backup[3];

	(void)argv;
	if (argc != 1)
		return (ft_too_many_args());
	setup_signals_main();
	env_minishell = ft_create_new_envp(envp);
	ft_backup_io(backup);
	ft_run_minishell_loop(env_minishell, backup);
	ft_close_backup(backup);
	return (g_status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	char	*cstr;
// 	char	*prompt;
// 	int		backup[2];
// 	char 	**env_minishell;
// 	t_tokenizer *tokens;

// 	backup[STDIN_FILENO] = dup(STDIN_FILENO);
// 	backup[STDOUT_FILENO] = dup(STDOUT_FILENO);
// 	(void)argv;
// 	setup_signals_main();
// 	env_minishell = ft_create_new_envp(envp);
// 	if (argc == 1)
// 	{
// 		while (1)
// 		{
// 			prompt = get_prompt();
// 			if (!prompt)
// 			{
// 				prompt = strdup("Minishell> ");
// 				if (!prompt)
// 					return (0);
// 			}
// 			printf("____________\nPID: %d\n", getpid());
// 			dup2(backup[STDIN_FILENO], STDIN_FILENO);
// 			dup2(backup[STDOUT_FILENO], STDOUT_FILENO);
// 			str = readline(prompt);
// 			if (str == NULL)
// 			{
// 				free(prompt);
// 				ft_free_array(env_minishell);
// 				ft_close_backup(backup);
// 				write(1, "exit\n", 5);
// 				g_status = errno;
// 				exit(g_status);
// 			}
// 			if (ft_check_isspace(str))
// 			{
// 				free(prompt);
// 				continue ;
// 			}
// 			if (ft_strlen(str) <= 0)
// 			{
// 				free(prompt);
// 				continue ;
// 			}
// 			if (g_status == STATUS_SIGINT_MAIN)
// 				printf("SIGINT CATCHED!\n");
// 			add_command_to_history(str);
// 			cstr = ft_preprocess_cmd_string(str);
// 			tokens = ft_parsing(cstr, env_minishell);
// 			if (!tokens)
// 			{
// 				printf("NO TOKENS\n");
// 				free(prompt);	
// 				ft_close_backup(backup);
// 				free(cstr);
// 				g_status = errno;
// 				continue ;	
// 			}
// 			if (ft_strncmp(cstr, "clear_history", 14) == 0)
// 			{
// 				clear_history_commands();
// 				printf("Command history cleared.\n");
// 			}
// 			free(cstr);
// 			free(prompt);
// 			if (ft_exec_minishell(&tokens, &env_minishell, backup) == FALSE)
// 			{
// 				g_status = errno;
// 				continue ;
// 			}
// 		}
// 		ft_close_backup(backup);
// 	}
// 	else
// 		printf("Too many arguments\n");
// 	return (g_status);
// }
