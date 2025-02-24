/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/24 08:31:35 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	disable_ctrl_c_echo(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		perror("tcgetattr");
	else
	{
		termios_p.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
			exit_error("tcsetattr");
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_clear_visible_line();;
		rl_redisplay();
	}
	else
		printf("%d\n", signum);
}

int		main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	(void)envp;

	struct sigaction sa;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_error("sigaction");
	disable_ctrl_c_echo();
	char *input;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		free(input);
	}
}
