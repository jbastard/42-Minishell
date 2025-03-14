/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   unset.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nlecreux <nlecreux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/25 11:59:44 by nlecreux		  #+#	#+#			 */
/*   Updated: 2025/02/25 13:47:28 by nlecreux		 ###   ########.fr	   */
/*																			*/
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

int	unset_command(char **args, t_minishell *main)
{
	// if (!args[0] || !is_valid_identifier(args[0]))
	// 	return (printf("unset: not a valid identifier\n"));
	if (check_env(args[0], main))
		main->env = ft_unset_env(main->env, args[0]);
	return (0);
}