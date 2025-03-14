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
