/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nlecreux <nlecreux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/25 11:59:13 by nlecreux		  #+#	#+#			 */
/*   Updated: 2025/02/25 11:59:13 by nlecreux		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_command(char **args, t_minishell *main)
{
	int			i;

	i = 0;
	(void)args;
	if (main->env)
	{
		while (main->env[i])
		{
			printf("%s\n", main->env[i]);
			i++;
		}
		return (0);
	}
	return (1);
}

char *get_variable_value(t_var *vars, char **envp, char *name)
{
	int i;
	size_t len;
	t_var *tmp;
	
	i = 0;
	len = ft_strlen(name);
	tmp = vars;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
