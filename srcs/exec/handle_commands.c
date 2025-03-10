/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:39:38 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/10 17:25:58 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_commands(char **args, t_minishell *main)
{
	int	i;

	i = is_builtin(main->builtins, args[0]);
	if (i)
		main->builtins[i].cmd(args + 1, main);
	else
	{
		printf("test\n");
	}
}

int	is_builtin(t_builtin *builtins, char *cmd)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (!ft_strncmp(builtins[i].cmd_name, cmd, ft_strlen(cmd)))
			return (i);
		i++;
	}
	return (0);
}
