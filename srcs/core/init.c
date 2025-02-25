/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:48 by nlecreux          #+#    #+#             */
/*   Updated: 2025/02/25 16:35:03 by nlecreux         ###   ########.fr       */
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
	return (main);
}

char	**copy_env(void)
{
	extern char	**environ;
	int			i;
	char		**new_env;

	i = 0;
	if (environ)
	{
		new_env = malloc(sizeof(char *) * (count_args(environ) + 1));
		if (!new_env)
			return (NULL);
		while (environ[i])
		{
			new_env[i] = ft_strdup(environ[i]);
			i++;
		}
		return (new_env);
	}
	return (NULL);
}

t_builtin	*init_builtins(void)
{
	t_builtin	*bi;
	int	i;

	i = -1;
	bi = malloc(8 * sizeof(t_builtin));
	if (!bi)
		return (NULL);
	bi[0].cmd_name = "echo";
	bi[0].cmd = echo_command;
	bi[1].cmd_name = "cd";
	bi[1].cmd = cd_command;
	bi[2].cmd_name = "pwd";
	bi[2].cmd = pwd_command;
	bi[3].cmd_name = "export";
	// bi[3].cmd = command_export;
	bi[4].cmd_name = "unset";
	// bi[4].cmd = command_unset;
	bi[5].cmd_name = "env";
	bi[5].cmd = env_command;
	bi[6].cmd_name = "exit";
	bi[6].cmd = exit_command;
	bi[7].cmd_name = NULL;
	while (++i <= 6)
		bi[i].size = ft_strlen(bi[i].cmd_name);
	return (bi);
}