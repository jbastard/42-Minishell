/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:00 by nlecreux          #+#    #+#             */
/*   Updated: 2025/05/05 09:42:20 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_num_args(int words, char **args, int i)
{
	i = 0;
	if (words >= 1)
	{
		while (args[0][i])
		{
			if (ft_isalpha(args[0][i++]))
				return (0);
		}
	}
	return (1);
}

int	exit_command(char **args, t_minishell *main)
{
	int	words;
	int	i;

	(void)main;
	i = 0;
	words = count_args(args);
	if (words == 0)
	{
		free_all(main);
		exit_error("", 0, 0);
	}
	i = (unsigned char)ft_atoi(args[0]);
	if (!exit_num_args(words, args, i))
		return (free_all(main), exit_error(ERROR_NUM_ARGS, 0, 2), 1);
	if (words == 1)
	{
		free_all(main);
		exit_error("", 0, i);
	}
	if (words >= 2)
		exit_error("exit\nminishell: exit: too many arguments\n", 0, -1);
	return (0);
}
