/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:42:36 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/15 09:31:09 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_tmp_name(int i)
{
	char	*num;
	char	*tmpname;

	num = ft_itoa(i);
	tmpname = ft_strjoin("heredoc_", num);
	free(num);
	return (tmpname);
}

int	heredoc(t_minishell *main, char *eof, char *filename)
{
	int		fd;
	char	*line;

	(void)main;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		return (printf("Unable to open heredoc\n"), 1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
		{
			free(line);
			break ;
		}
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
