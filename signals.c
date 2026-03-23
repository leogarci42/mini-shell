/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leogarci <leogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:54:21 by leogarci          #+#    #+#             */
/*   Updated: 2025/06/13 21:30:30 by leogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_status = STATUS_SIGINT_HEREDOC;
	write(1, "\n", 1);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	signal_int.sa_handler = heredoc_sigint_handler;
	sigemptyset(&signal_int.sa_mask);
	signal_int.sa_flags = 0;
	sigaction(SIGINT, &signal_int, NULL);
	signal_quit.sa_handler = SIG_IGN;
	sigemptyset(&signal_quit.sa_mask);
	signal_quit.sa_flags = 0;
	sigaction(SIGQUIT, &signal_quit, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_status == STATUS_OK || g_status == STATUS_SIGINT_MAIN)
	{
		g_status = STATUS_SIGINT_MAIN;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals_main(void)
{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	signal_int.sa_handler = handle_sigint;
	sigemptyset(&signal_int.sa_mask);
	signal_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal_int, NULL);
	signal_quit.sa_handler = SIG_IGN;
	sigemptyset(&signal_quit.sa_mask);
	signal_quit.sa_flags = 0;
	sigaction(SIGQUIT, &signal_quit, NULL);
}

void	setup_signals_child(void)
{
	struct sigaction	signal;

	g_status = STATUS_EXIT_CHILD;
	signal.sa_handler = SIG_DFL;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
