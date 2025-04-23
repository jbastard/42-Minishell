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
	int	j;

	if (handle_redir(main, cmd) != 0)
	{
		free_all(main);
		exit(1);
	}
	if (i >= 0)
	{
		j = main->builtins[i].cmd(cmd->cmd_args + 1, main);
		free_all(main);
		exit(j);
	}
	execute_external_command(cmd, main);
	free_all(main);
	exit(main->last_status);
}

int	exec_one_cmd(t_cmd *cmd, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, cmd->cmd_args[0]);
	if (i >= 0 && !cmd->redir)
		main->last_status = main->builtins[i].cmd(cmd->cmd_args + 1, main);
	if ((i < 0 || cmd->redir) && bi_has_output(i, cmd->cmd_args + 1))
	{
		if (!cmd->path)
			return (ft_dprintf(2, "%s: command not found\n", cmd->cmd_args[0]), 0);
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
	return (1);
}

void	exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	int		pipefd[2];
	int		j;

	pipefd[0] = 0;
	while (cmds)
	{
		j = 1;
		if (!create_pipe_and_fork(cmds, main, prev_pipe, pipefd))
			j = 0;
		if (cmds->pid > 0)
		{
			if (cmds->next && cmds->next->path)
				close(pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			if (pipefd[0])
				prev_pipe = pipefd[0];
			if (cmds->next)
				cmds = cmds->next;
			else
				break ;
		}
		else if (cmds->pid == -1)
			cmds = cmds->next;
	}
	if (j)
		waitpid(cmds->pid, &main->last_status, 0);
	if (WIFEXITED(main->last_status))
		main->last_status = WEXITSTATUS(main->last_status);
	else if (WIFSIGNALED(main->last_status))
		main->last_status = 128 + WTERMSIG(main->last_status);
	if (prev_pipe != -1)
		close(prev_pipe);
}
