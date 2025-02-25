/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 17:59:24 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	append_nodes(t_cmd *cmd)
{

}

/// transformer
void 	parse_exec_cmd(char *line, t_minishell minishell)
{
	char	**split_line;
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof (t_cmd));
	split_line = ft_ws_split(line);

	while (split_line)
	{
		append_nodes(cmd_list, );
	}
}

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

