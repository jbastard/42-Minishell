/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:28:40 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/14 15:31:56 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env(char *env, t_minishell *main)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(env + 1);
	while (main->env[i])
	{
		if (!ft_strncmp(env, main->env[i], j))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_realloc_tab(char **args, char *env)
{
	int		count;
	char	**new;
	int		i;

	count = count_args(args);
	new = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = ft_strdup(env);
	new[i + 1] = NULL;
	free_tab(args);
	return (new);
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

char	**copy_env(void)
{
	extern char	**environ;
	int			i;
	char		**new_env;

	i = 0;
	if (environ)
	{
		new_env = malloc(sizeof(char *) * (count_args(environ) + 1));
		if (!new_env)
			return (NULL);
		while (environ[i])
		{
			new_env[i] = ft_strdup(environ[i]);
			i++;
		}
		new_env[i] = NULL;
		return (new_env);
	}
	return (NULL);
}
