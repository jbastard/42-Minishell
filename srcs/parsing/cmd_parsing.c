/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 16:33:06 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_prompt(t_minishell *main)
{
	char	buffer[PATH_MAX];
	if (main->prompt)
		free(main->prompt);
	getcwd(buffer, PATH_MAX);
	main->prompt = ft_strjoin(buffer, ">");
}

char	*get_cmd(t_minishell *main)
{
	char	*line;
	
	update_prompt(main);
	line = readline(main->prompt);
	return (line);
}
