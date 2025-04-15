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
				exit_error("minishell: exit: numeric argument required\n", 0, 2);
		}
	}
	if (words == 1)
		exit_error("", 0, (unsigned char)ft_atoi(args[0]));
	if (words >= 2)
		exit_error("exit\nminishell: exit: too many arguments\n", 0, -1);
	return (0);
}
