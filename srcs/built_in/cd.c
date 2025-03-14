/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:37:51 by nlecreux          #+#    #+#             */
/*   Updated: 2025/02/25 11:37:51 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_command(char **args, t_minishell *main)
{
	char	buffer[1024];
	char	*new_path[2];

	(void)main;
	if (args == NULL || args[0][0] == 0)
		return (1);
	if (args[0][0] == '/')
	{
		if (chdir(args[0]) != 0)
			perror("cd");
	}
	else
	{
		if (getcwd(buffer, 1024))
		{
			new_path[0] = ft_strjoin(buffer, "/");
			new_path[1] = ft_strjoin(new_path[0], args[0]);
			if (chdir(new_path[1]) != 0)
				perror("cd");
			return (free(new_path[0]), free(new_path[1]), 0);
		}
		else
			perror("cd");
	}
	return (0);
}
