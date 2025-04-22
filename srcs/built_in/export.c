/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nlecreux <nlecreux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/25 11:59:20 by nlecreux		  #+#	#+#			 */
/*   Updated: 2025/02/25 14:18:08 by nlecreux		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**change_env(char *env, t_minishell *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (!ft_strncmp(env, main->env[i], len_equal(env)))
		{
			free(main->env[i]);
			main->env[i] = ft_strdup(env);
			return (main->env);
		}
		i++;
	}
	return (main->env);
}

int	find_node_env(char *env, t_minishell *main)
{
	t_env	*current;
	char	*temp;
	int		i;

	current = main->local_vars;
	temp = ft_strchr(env, '=');
	while (current)
	{
		if (temp)
			i = ft_strlen(env) - ft_strlen(temp) - 1;
		else
		{
			if (ft_strlen(env) > ft_strlen(current->key))
				i = ft_strlen(env);
			else
				i = ft_strlen(current->key);
		}
		if (!ft_strncmp(current->key, env, i))
			return (1);
		current = current->next;
	}
	return (0);
}

void	replace_value_env(char *env, t_minishell *main)
{
	t_env	*current;
	char	*temp;

	current = main->local_vars;
	while (current)
	{
		if (!ft_strncmp(current->key, env, ft_strlen(current->key)))
		{
			if (current->value)
				free(current->value);
			temp = ft_strchr(env, '=');
			if (!temp)
				current->value = NULL;
			else if (*(temp + 1) == 0)
				current->value = ft_strdup("");
			else
				current->value = ft_strdup(temp + 1);
			return ;
		}
		current = current->next;
	}
}

int	export_command(char	**args, t_minishell *main)
{
	int	i;

	i = 0;
	if (!args[0])
		print_locals(main);
	while (args[i])
	{
		{
			if (!is_valid_identifier(args[i]))
				return (printf("minishell : export: '%s': not a valid identifier\n", args[i]), 1);
			if (ft_strchr(args[i], '='))
			{
				if (!check_env(args[i], main))
					main->env = ft_realloc_tab(main->env, args[i]);
				else
					main->env = change_env(args[i], main);
			}
			if (!find_node_env(args[i], main))
				add_node_env(args[i], main);
			else
				replace_value_env(args[i], main);
			i++;
		}
	}
	return (1);
}
