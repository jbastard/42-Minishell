/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:13:10 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/14 16:22:45 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_minishell	init_minishell(void)
{
	t_minishell	main;

	main.builtins = init_builtins();
	main.local_vars = NULL;
	main.env = copy_env();
	main.prompt = NULL;
	main.last_status = ERR_NONE;
	init_local_env(&main);
	return (main);
}

t_builtin	*init_builtins(void)
{
	t_builtin	*bi;

	bi = malloc(9 * sizeof(t_builtin));
	if (!bi)
		return (NULL);
	bi[0].cmd_name = "echo";
	bi[0].cmd = echo_command;
	bi[1].cmd_name = "cd";
	bi[1].cmd = cd_command;
	bi[2].cmd_name = "pwd";
	bi[2].cmd = pwd_command;
	bi[3].cmd_name = "export";
	bi[3].cmd = export_command;
	bi[4].cmd_name = "unset";
	bi[4].cmd = unset_command;
	bi[5].cmd_name = "env";
	bi[5].cmd = env_command;
	bi[6].cmd_name = "exit";
	bi[6].cmd = exit_command;
	bi[7].cmd_name = "mordex";
	bi[7].cmd = mordex_command;
	return (bi);
}

void	init_local_env(t_minishell *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		add_node_env(main->env[i], main);
		i++;
	}
	sort_local_env(&(main->local_vars));
}
