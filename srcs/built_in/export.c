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

char	**ft_realloc_env(char **args, char *env)
{
	int		count;
	char	**new;
	int		i1;
	int		i2;

	count = count_args(args);
	new = malloc(sizeof(char *) * (count + 2));
	i1 = 0;
	while (args[i1])
	{
		new[i1] = ft_strdup(args[i1]);
		i1++;
	}
	i2 = 0;
	new[i1] = ft_strdup(env);
	new[i1 + 1] = NULL;
	free_tab(args);
	return (new);
}

int	char_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

int	export_command(char	**args, t_minishell *main)
{
	// if (!args[0] || !is_valid_identifier(args[0]))
	// 	return (printf("export: not a valid identifier"));
	if (char_in(args[0], '='))
	{
		if (!check_env(args[0], main))
			main->env = ft_realloc_env(main->env, args[0]);
		else
			main->env = change_env(args[0], main);
	}
	return (0);
}
