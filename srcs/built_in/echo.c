/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:58:57 by nlecreux          #+#    #+#             */
/*   Updated: 2025/02/25 15:08:30 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_command(char **args, t_minishell *main)
{
	int	newl;
	int	i;

	(void)main;
	newl = 1;
	i = 0;
	if (!(ft_strncmp(args[i], "-n", 2)))
	{
		newl = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newl)
		printf("\n");
	return (0);
}
