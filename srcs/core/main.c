/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/18 08:59:20 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_inputs(t_minishell *main)
{
	if (!main->is_here && g_signal != SIG_CHILD)
		main->line = readline(main->prompt);
	if (!main->line)
		return (0);
	if (!get_cmd(main))
		return (free(main->line), 1);
	add_history(main->line);
	handle_commands(main->cmd, main);
	free_cmd(main->cmd);
	if (main->line)
		return (free(main->line), 1);
	return (1);
}

int	main(void)
{
	t_minishell	main;

	main = init_minishell();
	while (1)
	{
		set_sig_interactive();
		update_prompt(&main);
		if (!handle_inputs(&main))
			break ;
	}
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	free_local_env(&main.local_vars);
	rl_clear_history();
}
