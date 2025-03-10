/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/10 18:00:55 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_local_env(t_env **env)
{
	t_env	*temp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = temp;
	}
	*env = NULL;
}

int	main(void)
{
	char		*line;
	char		**temp;
	t_minishell	main;

	main = init_minishell();
	sig_handler();
	while (1)
	{
		line = get_cmd(&main);
		if (!line)
			break ;
		temp = ft_split(line, ' ');
		if (temp[0])
		{
			add_history(line);
			handle_commands(temp, &main);
		}
		if (temp)
			free_tab(temp);
		free(line);
	}
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	free_local_env(&(main.local_vars));
	rl_clear_history();
}
