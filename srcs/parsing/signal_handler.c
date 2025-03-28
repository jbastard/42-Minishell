/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:27:07 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 10:23:18 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal = 0;

static void	handle_sigint_interactive(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sig_executing(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (signo == SIGQUIT)
	{
		g_signal = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
}

void	init_sigaction(struct sigaction *sa, void (*handler)(int), int flags)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = handler;
	sa->sa_flags = flags;
}

void	set_sig_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	init_sigaction(&sa_int, handle_sigint_interactive, SA_RESTART);
	init_sigaction(&sa_quit, SIG_IGN, 0);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_sig_executing(void)
{
	struct sigaction	sa_exec;

	ft_memset(&sa_exec, 0, sizeof(sa_exec));
	init_sigaction(&sa_exec, handle_sig_executing, SA_RESTART);
	sigaction(SIGINT, &sa_exec, NULL);
	sigaction(SIGQUIT, &sa_exec, NULL);
}
