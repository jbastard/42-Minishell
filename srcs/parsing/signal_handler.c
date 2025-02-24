/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:27:07 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/24 11:44:07 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Comme son nom l'indique, cette fonction permet de désactiver l affichage des signaux de  contrôle (ctrl-c, ctrl-d,..)
 * La structure de type termios permet de stocker les paramètres du terminal
 * La fonction tcgetattr récupère les attributs actuels du terminal associé à l'entrée standard (clavier).
 * termios_p.c_lflag &= ~ECHOCTL désactive l'affichage des caractères de contrôle (comme ^C, ^D) en supprimant l'option ECHOCTL.
 * La fonction tcsetattr applique immédiatement les nouvelles configurations au terminal.
 */
void	disable_ctrl_echo(void)
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

void 	ctrl_c(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void 	do_nothing(int signal)
{
	(void)signal;
	return ;
}

void	sig_handler()
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}