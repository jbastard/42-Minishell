/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/04 10:57:06 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_prompt(t_minishell *mnsl)
{
	char	buffer[PATH_MAX];
	if (mnsl->prompt)
		free(mnsl->prompt);
	getcwd(buffer, PATH_MAX);
	mnsl->prompt = ft_strjoin(buffer, ">");
}

char	*get_cmd(t_minishell *mnsl)
{
	char	*line;
	
	update_prompt(mnsl);
	line = readline(mnsl->prompt);
	return (line);
}

