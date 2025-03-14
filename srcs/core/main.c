/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/14 15:28:18 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
