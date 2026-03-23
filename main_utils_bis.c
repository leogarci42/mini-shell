/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:05:01 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/15 13:46:53 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	ft_check_isspace(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (FALSE);
	return (TRUE);
}

void	ft_backup_io(int backup[3])
{
	backup[STDIN_FILENO] = dup(STDIN_FILENO);
	backup[STDOUT_FILENO] = dup(STDOUT_FILENO);
	backup[EXIT_STATUS] = 0;
}

int	ft_too_many_args(void)
{
	printf("Too many arguments\n");
	return (1);
}

static void	ft_process_input_line(char *str, char *prompt, char ***env_minishell
	, int *backup)
{
	char		*cstr;
	t_tokenizer	*tokens;

	add_command_to_history(str);
	cstr = ft_preprocess_cmd_string(str);
	tokens = ft_parsing(cstr, *env_minishell, backup);
	if (!tokens)
	{
		ft_handle_no_tokens(cstr, prompt, backup);
		return ;
	}
	ft_handle_clear_history(cstr);
	free(cstr);
	free(prompt);
	if (ft_exec_minishell(&tokens, env_minishell, backup) == FALSE)
	{
		if (g_status != STATUS_SIGINT_HEREDOC)
			backup[EXIT_STATUS] = errno;
	}
}

void	ft_run_minishell_loop(char **env_minishell, int *backup)
{
	char	*str;
	char	*prompt;

	while (1)
	{
		g_status = STATUS_OK;
		prompt = ft_get_prompt_safe();
		ft_restore_io(backup);
		str = readline(prompt);
		if (!ft_handle_null_input(str, prompt, env_minishell, backup))
			continue ;
		if (g_status == STATUS_SIGINT_MAIN)
			backup[EXIT_STATUS] = 130;
		if (ft_check_isspace(str) || ft_strlen(str) <= 0)
		{
			g_status = STATUS_OK;
			ft_continue_empty(prompt, str);
			continue ;
		}
		ft_process_input_line(str, prompt, &env_minishell, backup);
	}
}
