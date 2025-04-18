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
	(void)signo;
	if (g_signal == SIG_EXEC)
		return ;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	if (g_signal == SIG_INTER || g_signal == SIG_CHILD)
		rl_redisplay();
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
