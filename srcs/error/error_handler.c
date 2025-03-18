/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:44 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/18 12:14:59 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		free(redir->file);
		redir = redir->next;
		free(tmp);
	}
	redir = NULL;
}

void 	free_cmd(t_cmd *cmd)
{
	t_cmd 	*tmp;

	while (cmd)
	{
		free(cmd->path);
		free_tab(cmd->cmd_args);
		free_redir(cmd->redir);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	cmd = NULL;
}

int		handle_error(t_minishell *main, t_error_type type, char *info)
{
	if (!main)
		return (1);
	if (type == ERR_NONE)
		return (0);
	if (type == ERR_SYNTAX)
	{
		ft_dprintf(2, "minishell:"
					  " syntax error near unexpected token `%s'\n", info);
		main->last_status = 2;
	}
	if (type == ERR_PIPE)
	{
		ft_dprintf(2, "minishell:"
					  " syntax error near unexpected token `%s'\n", info);
		main->last_status = 2;
	}
	if (type == ERR_CMD_NOT_FOUND)
	{
		ft_dprintf(2, "minishell:"
					  " command not found: %s\n", info);
		main->last_status = 127;
	}
	if (type == ERR_PERMISSION_DENIED)
	{
		ft_dprintf(2, "minishell:"
					  " permission denied: %s\n", info);
		main->last_status = 126;
	}
	if (type == ERR_FILE_NOT_FOUND)
	{
		ft_dprintf(2, "minishell:"
					  " no such file or directory: %s\n", info);
		main->last_status = 126;
	}

//	free_cmd(main->cmd);
	return (main->last_status);
}

void 	exit_error(char *source, int isper, int exitcode)
{
	if (exitcode >= 0)
		printf("exit\n");
	if (isper)
		perror(source);
	else if (source)
			printf("%s", source);
	if (exitcode >= 0)
		exit(exitcode);
}
