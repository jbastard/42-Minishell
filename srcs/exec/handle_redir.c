/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:42:36 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/21 14:27:13 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int heredoc(t_minishell *main, char *eof)
{
	int		fd;
	char	*line;

	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		return (printf("Unable to open heredoc\n"), 1);
	main->is_here = 1;
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
	main->is_here = 0;
	return (0);
}

int redir_in(t_minishell *main, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 664);
	if (fd < 0)
		return (handle_error(main, ERR_FILE_NOT_FOUND, file));
	else if (access(file, O_RDONLY))
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int redir_out(t_minishell *main, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		return (1);
	else if (access(file, O_RDONLY))
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int redir_append(t_minishell *main, char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd < 0)
		return (1);
	else if (access(file, O_RDONLY))
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redir(t_minishell *main, t_cmd *cmd)
{
	t_redir *redir = cmd->redir;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			return (redir_in(main, redir->file));
		else if (redir->type == TOKEN_REDIR_OUT)
			return (redir_out(main, redir->file));
		else if (redir->type == TOKEN_APPEND)
			return (redir_append(main, redir->file));
		else if (redir->type == TOKEN_HEREDOC)
			if (!heredoc(main, redir->file))
				return (redir_in(main, "heredoc.tmp"));
		redir = redir->next;
	}
	return (0);
}
