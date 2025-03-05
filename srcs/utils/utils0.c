/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:35:38 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/05 12:40:03 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	i = 0, count = 0;
	while (args[i])
	{
		i++;
		count++;
	}
	return (count);
}

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

int	check_env(char *env, t_minishell *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (!ft_strncmp(env, main->env[i], len_equal(env)))
			return (1);
		i++;
	}
	return (0);
}

int	len_equal(char	*env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	return (i);
}

// int	is_valid_identifier()