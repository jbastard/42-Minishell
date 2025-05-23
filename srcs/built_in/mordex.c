/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mordex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:08:06 by nlecreux          #+#    #+#             */
/*   Updated: 2025/04/24 14:19:20 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mordex_command(char **args, t_minishell *main)
{
	int		fd;
	char	*line;

	(void)args;
	(void)main;
	fd = open(MORDEX_PATH, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	free(line);
	close(fd);
	return (1);
}
