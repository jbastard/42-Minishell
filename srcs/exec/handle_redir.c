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

	if (access(file, R_OK))
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (handle_error(main, ERR_FILE_NOT_FOUND, file));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_out(t_minishell *main, char *file)
{
	int	fd;
	
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		return (handle_error(main, ERR_FILE_NOT_FOUND, file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_append(t_minishell *main, char *file)
{
	int	fd;
	
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
		return (handle_error(main, ERR_PERMISSION_DENIED, file));
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd < 0)
		return (handle_error(main, ERR_FILE_NOT_FOUND, file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redir(t_minishell *main, t_cmd *cmd)
{
	t_redir	*redir;
	int		ret;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			ret = redir_in(main, redir->file);
		else if (redir->type == TOKEN_REDIR_OUT)
			ret = redir_out(main, redir->file);
		else if (redir->type == TOKEN_APPEND)
			ret = redir_append(main, redir->file);
		if (ret != 0)
			return (ret);
		redir = redir->next;
	}
	return (0);
}
