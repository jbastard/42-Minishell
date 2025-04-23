/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:00 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/10 17:14:08 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_command(char **args, t_minishell *main)
{
	int	words;
	int	i;

	(void)main;
	i = 0;
	words = count_args(args);
	if (words == 0)
		exit_error("", 0, 0);
	if (words >= 1)
	{
		while (args[0][i])
		{
			if (ft_isalpha(args[0][i++]))
				return (free_all(main), exit_error(ERROR_NUM_ARGS, 0, 2), 1);
		}
	}
	i = (unsigned char)ft_atoi(args[0]);
	free_all(main);
	if (words == 1)
		exit_error("", 0, i);
	if (words >= 2)
		exit_error("exit\nminishell: exit: too many arguments\n", 0, -1);
	return (0);
}
