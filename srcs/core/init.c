/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:13:10 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/18 12:46:35 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_history(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i++] != ' ')
			return (1);
	return (0);
}

t_minishell	init_minishell(void)
{
	t_minishell	main;

	main.builtins = init_builtins();
	main.local_vars = NULL;
	main.last_status = ERR_NONE;
	main.env = copy_env();
	main.prompt = NULL;
	main.is_here = 0;
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

void	init_lexer(t_lexer *lexer, const char *input)
{
	lexer->input = input;
	lexer->input_len = ft_strlen(input);
	lexer->tokens = NULL;
	lexer->i = 0;
	lexer->force_token = 0;
	lexer->j = 0;
	lexer->quote = 0;
	lexer->error = 0;
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
