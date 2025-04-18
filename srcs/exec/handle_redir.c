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

int	redir_in(t_minishell *main, char *file)
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

int	redir_out(t_minishell *main, char *file)
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

int	redir_append(t_minishell *main, char *file)
{
	int	fd;

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
	t_redir	*redir;
	int		i;
	char	*tmpname;

	redir = cmd->redir;
	i = 0;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			redir_in(main, redir->file);
		else if (redir->type == TOKEN_REDIR_OUT)
			redir_out(main, redir->file);
		else if (redir->type == TOKEN_APPEND)
			redir_append(main, redir->file);
		else if (redir->type == TOKEN_HEREDOC)
		{
			tmpname = generate_tmp_name(i++);
			if (!heredoc(main, redir->file, tmpname))
				redir_in(main, tmpname);
			unlink(tmpname);
			free(tmpname);
		}
		redir = redir->next;
	}
	return (0);
}
