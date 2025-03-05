/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:24:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/05 15:56:41 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_whitespaces(char c)
{
	return (c <= 32);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

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