/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_history_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:41:36 by leogarci          #+#    #+#             */
/*   Updated: 2025/04/21 22:53:28 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_to_history(const char *command)
{
	if (command && *command)
		add_history(command);
}

void	clear_history_commands(void)
{
	rl_clear_history();
}
