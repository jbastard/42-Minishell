/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils_env0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:56:46 by nlecreux          #+#    #+#             */
/*   Updated: 2025/04/24 14:08:32 by nlecreux         ###   ########.fr       */
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

t_env	*create_env_node(char *env)
{
	t_env	*new_node;
	char	*equal_pos;
	size_t	key_len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_pos = ft_strchr(env, '=');
	key_len = equal_pos - env;
	if (equal_pos)
	{
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

int	close_pipes(t_cmd **cmd, int *prev_pipe, int *pipefd)
{
	if ((*cmd)->next && (*cmd)->next->path)
		close(pipefd[1]);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipefd[0])
		*prev_pipe = pipefd[0];
	if ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	else
		return (0);
	return (1);
}
