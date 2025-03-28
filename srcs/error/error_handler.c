/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:44 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/28 10:42:09 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(t_minishell *main, t_error_type type, char *info)
{
	if (!main)
		return (1);
	else if (type == ERR_NONE)
		return (0);
	else if (type == ERR_SYNTAX)
	{
		ft_dprintf(2, "minishell:"
			" syntax error near unexpected token `%s'\n", info);
		main->last_status = 2;
	}
	else if (type == ERR_PIPE)
	{
		ft_dprintf(2, "minishell:"
			" syntax error near unexpected token `%s'\n", info);
		main->last_status = 2;
	}
	else if (type == ERR_CMD_NOT_FOUND)
	{
		ft_dprintf(2, "minishell:"
			" command not found: %s\n", info);
		main->last_status = 127;
	}
	else
		handle_error1(main, type, info);
	return (main->last_status);
}

int	handle_error1(t_minishell *main, t_error_type type, char *info)
{
	if (type == ERR_FILE_NOT_FOUND)
	{
		ft_dprintf(2, "minishell:"
			" no such file or directory: %s\n", info);
		main->last_status = 127;
	}
	else if (type == ERR_PERMISSION_DENIED)
	{
		ft_dprintf(2, "minishell:"
			" permission denied: %s\n", info);
		main->last_status = 126;
	}
}

void	exit_error(char *source, int isper, int exitcode)
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
