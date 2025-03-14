/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:56:46 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/10 17:29:02 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_env(char *env, t_minishell *main)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_env_node(env);
	if (!new_node)
		return ;
	if (main->local_vars == NULL)
		main->local_vars = new_node;
	else
	{
		current = main->local_vars;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
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

t_env	*create_env_node(char *env)
{
	t_env	*new_node;
	char	*equal_pos;
	size_t	key_len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_pos = ft_strchr(env, '=');
	if (equal_pos)
	{
		key_len = equal_pos - env;
		new_node->key = malloc(key_len + 1);
		if (!new_node->key)
			return (free(new_node), NULL);
		ft_memcpy(new_node->key, env, key_len);
		new_node->key[key_len] = 0;
		new_node->value = ft_strdup(equal_pos + 1);
	}
	else
	{
		new_node->key = ft_strdup(env);
		new_node->value = NULL;
	}
	new_node->next = NULL;
	return (new_node);
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

void	print_locals(t_minishell *main)
{
	t_env	*test;

	test = main->local_vars;
	while (test)
	{
		if (test->value)
			printf("declare -x %s=\"%s\"\n", test->key, test->value);
		else
			printf("declare -x %s\n", test->key);
		test = test->next;
	}
}
