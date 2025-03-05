/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mordex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:08:06 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/05 14:14:53 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mordex_command(char **args, t_minishell *main)
{
	(void)args;
	(void)main;
	int		fd;
	char	*line;

	fd = open(MORDEX_PATH, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	return (1);
}