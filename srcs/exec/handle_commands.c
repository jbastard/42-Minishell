/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:39:38 by nlecreux          #+#    #+#             */
/*   Updated: 2025/02/25 16:40:16 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_commands(char **args, t_minishell *main)
{
	int	i;

	i = 0;
	while (main->builtins[i].cmd_name)
	{
		if (!ft_strncmp(main->builtins[i].cmd_name, args[0], main->builtins[i].size))
			main->builtins[i].cmd(args + 1, main);
		i++;
	}
}
