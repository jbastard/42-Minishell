/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:27:07 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/15 09:17:57 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal = 0;

static void	handle_sigint_interactive(int signo)
{
	if (g_signal == SIG_CHILD)
		return ;
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sig_executing(int signo)
{
	(void)signo;

	if (g_signal == SIG_EXEC)
		handle_sigint_interactive(signo);
	else if (signo == SIGQUIT)
	{
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
	g_signal = SIG_INTER;

	init_sigaction(&sa_int, handle_sigint_interactive, SA_RESTART);
	init_sigaction(&sa_quit, SIG_IGN, 0);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_sig_executing(void)
{
	struct sigaction	sa_exec;
	g_signal = SIG_EXEC;

	init_sigaction(&sa_exec, handle_sig_executing, SA_RESTART);
	sigaction(SIGINT, &sa_exec, NULL);
	sigaction(SIGQUIT, &sa_exec, NULL);
}

static void	handle_sigint_child(int signo)
{
	(void)signo;

	if (g_signal == SIG_CHILD)
		exit(130);
}

void set_sig_child(void)
{
	struct sigaction sa_child;
	g_signal = SIG_CHILD;
	ft_memset(&sa_child, 0, sizeof(sa_child));
	init_sigaction(&sa_child, handle_sigint_child, 0);
	sigaction(SIGINT, &sa_child, NULL);
	sigaction(SIGQUIT, &sa_child, NULL);
}
