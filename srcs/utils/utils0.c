/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:35:38 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/10 17:27:33 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env(char *env, t_minishell *main)
{
	int	i;
	int	j;

	i = 0;
	while (main->env[i])
	{
		j = len_equal(main->env[i]);
		if (j < len_equal(env))
			j = len_equal(env);
		if (!ft_strncmp(env, main->env[i], j))
			return (1);
		i++;
	}
	return (0);
}

int	count_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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

int	is_valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_' || name[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	len_equal(char	*env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	return (i);
}
