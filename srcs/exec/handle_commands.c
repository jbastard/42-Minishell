/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:58:04 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/18 11:37:10 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_commands(t_cmd *cmds, t_minishell *main)
{
	int	cmd_count;
	int	prev_pipe;

	prev_pipe = -1;
	cmd_count = count_commands(cmds);
	preprocess_heredocs(main, main->cmd);
	if (cmd_count == 1)
		exec_one_cmd(cmds, main);
	else
		exec_multiple_cmds(cmds, main, prev_pipe);
	cleanup_heredoc_files(cmds);
}

int	bi_has_output(int i, char **args)
{
	if (i == 0 || i == 2 || (i == 3 && !*args) || i == 5 || i == 7 || i < 0)
		return (1);
	return (0);
}

void	exec_cmd_child(t_cmd *cmd, t_minishell *main, int i)
{
	handle_redir(main, cmd);
	if (i >= 0)
		exit(main->builtins[i].cmd(cmd->cmd_args + 1, main));
	execute_external_command(cmd, main);
	exit(main->last_status);
}

void	exec_one_cmd(t_cmd *cmd, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, cmd->cmd_args[0]);
	if (i >= 0 && !cmd->redir)
		main->last_status = main->builtins[i].cmd(cmd->cmd_args + 1, main);
	if ((i < 0 || cmd->redir) && bi_has_output(i, cmd->cmd_args + 1))
	{
		if (!cmd->path)
			return;
		pid = fork();
		if (pid == 0)
		{
			exec_cmd_child(cmd, main, i);
			free_all(main);
		}
		waitpid(pid, &main->last_status, 0);
		if (WIFEXITED(main->last_status))
			main->last_status = WEXITSTATUS(main->last_status);
		else if (WIFSIGNALED(main->last_status))
			main->last_status = 128 + WTERMSIG(main->last_status);
	}
	else if (i >= 0 && cmd->redir && !bi_has_output(i, cmd->cmd_args + 1))
		main->last_status = main->builtins[i].cmd(cmd->cmd_args + 1, main);
}

void	exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	int		pipefd[2];

	while (cmds)
	{
		create_pipe_and_fork(cmds, main, prev_pipe, pipefd);
		if (cmds->pid > 0)
		{
			close(pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			prev_pipe = pipefd[0];
			if (cmds->next)
				cmds = cmds->next;
			else
				break ;
		}
	}
	waitpid(cmds->pid, &main->last_status, 0);
	if (WIFEXITED(main->last_status))
		main->last_status = WEXITSTATUS(main->last_status);
	else if (WIFSIGNALED(main->last_status))
		main->last_status = 128 + WTERMSIG(main->last_status);
	if (prev_pipe != -1)
		close(prev_pipe);
}
