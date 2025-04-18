/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:42:36 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/18 10:09:59 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	preprocess_heredocs(t_minishell *main, t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		i = 0;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				char *tmpname = generate_tmp_name(i++);
				if (heredoc(main, redir->file, tmpname))
				{
					unlink(tmpname);
					free(tmpname);
					return;
				}
				free(redir->file);
				redir->file = tmpname;
				redir->type = TOKEN_REDIR_IN;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

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
	g_signal = SIG_CHILD;
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
	g_signal = SIG_EXEC;
	return (0);
}
