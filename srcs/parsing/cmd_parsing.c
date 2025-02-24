/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/24 15:33:07 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_cmd(char *line)
{
	char	**exline;
	int		words;
	int		i;

	i = 0;
	words = word_count(line, ' ');
	exline = ft_split(line, ' ');
	if (words == 1)
		exit_error("", 0, 1);
	else if (words >= 2)
	{
		while (exline[1][i])
		{
			if (ft_isalpha(exline[1][i++]))
				exit_error("bash: exit: numeric argument required\n", 0, 2);
		}
	}
	if (words == 2)
		exit (ft_atoi(exline[1]));
	else if (words >= 3)
			exit_error("bash: exit: too many arguments\n", 0, 1);
}

char	*get_cmd(char **envp)
{
	char	*line;

	(void)envp;
	line = readline(PROMPT);
	if (!line)
		return (NULL);
	if (!ft_strncmp(line, "exit", 4))
		exit_cmd(line);
	return (line);
}
