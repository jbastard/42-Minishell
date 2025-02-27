/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/26 15:48:21 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_into_toks(t_minishell *mnsl, char *line)
{

	int	i;
	int q_temp;
	int q_flag;

	i = 0;
	q_flag = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			q_flag = SQUOTES;
		if (line[i] == '"')
			q_flag = DQUOTES;
		q_temp = q_flag;
		while (line[i] <= 32 && q_flag == 0)
			i++;
		while (line[i] > 32)
			printf("%c", line[i]);
		if (line[i] == '\'' && q_flag == SQUOTES)
			q_flag = 0;
		if (line[i] == '"' && q_flag == DQUOTES)
			q_flag = 0;
	}
}

void 	lex_line(t_minishell *mnsl, char *line)
{
	int		i;
	char	**splited_line;

	i = 0;
	splited_line = split_cmd(line, mnsl);
	while (splited_line[i])
		printf("%s\n", splited_line[i++]);
}

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

