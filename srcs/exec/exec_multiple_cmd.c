/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:20:23 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/03 11:20:27 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_wait_and_cleanup(t_cmd *cmd,
									t_minishell *main,
									int prev_pipe)
{
	int	last_status;

	last_status = -1;
	while (cmd)
	{
		last_status = -1;
		waitpid(cmd->pid, &last_status, 0);
		if (WIFEXITED(last_status))
			main->last_status = WEXITSTATUS(last_status);
		else if (WIFSIGNALED(last_status))
			main->last_status = 128 + WTERMSIG(last_status);
		cmd = cmd->next;
	}
	if (prev_pipe != -1)
		close(prev_pipe);
}

void	exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		j;

	cmd = cmds;
	pipefd[0] = 0;
	while (cmds)
	{
		if (!cmds->cmd_args)
		{
			cmds = cmds->next;
			continue ;
		}
		j = create_pipe_and_fork(cmds, main, prev_pipe, pipefd);
		if (j == 127)
			main->last_status = 127;
		if (cmds->pid > 0)
		{
			if (!close_pipes(&cmds, &prev_pipe, pipefd))
				break ;
		}
		else if (cmds->pid == -1)
			cmds = cmds->next;
	}
	handle_wait_and_cleanup(cmd, main, prev_pipe);
}
