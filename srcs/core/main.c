/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 16:43:28 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main()
{
	char		*line;
	t_minishell	main;
	
	main = init_minishell();
	sig_handler();
	while(1)
	{
		line = get_cmd(&main);
		if (!line)
			break ;
		if (line[0] != 0)
			add_history(line);
		handle_commands(ft_split(line, ' '), &main);
		free(line);
	}
	rl_clear_history();
}
