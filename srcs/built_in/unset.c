/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 06:54:10 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/22 08:44:32 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_unset_env(char **env, char *var)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = count_args(env);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
			free(env[i]);
		else
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}

void	remove_node_env(char *env, t_minishell *main)
{
	t_env	*current;
	t_env	*prev;

	current = main->local_vars;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, env, ft_strlen(env)))
		{
			if (prev)
				prev->next = current->next;
			else
				main->local_vars = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free (current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_command(char **args, t_minishell *main)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!args[i] || !is_valid_identifier(args[i]))
			return (printf("minishell: unset: "
					"'%s': not a valid identifier\n", args[i]), 1);
		if (check_env(args[i], main))
			main->env = ft_unset_env(main->env, args[i]);
		if (find_node_env(args[i], main))
			remove_node_env(args[i], main);
		i++;
	}
	return (0);
}
