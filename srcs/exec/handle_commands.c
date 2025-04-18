/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:58:04 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/18 10:14:20 by jbastard         ###   ########.fr       */
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
}

int	bi_has_output(int i, char **args)
{
	if (i == 0 || i == 2 || (i == 3 && !*args) || i == 5 || i == 7 || i < 0)
		return (1);
	return (0);
}

void	exec_one_cmd(t_cmd *cmd, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, cmd->cmd_args[0]);
	if (i >= 0 && (bi_has_output(i, cmd->cmd_args + 1) && !cmd->redir))
		main->builtins[i].cmd(cmd->cmd_args + 1, main);
	else if (i >= 0 && !cmd->redir)
		main->builtins[i].cmd(cmd->cmd_args + 1, main);
	if ((i < 0 || cmd->redir) && bi_has_output(i, cmd->cmd_args + 1))
	{
		pid = fork();
		if (pid == 0)
		{
			handle_redir(main, cmd);
			if (i >= 0)
				main->builtins[i].cmd(cmd->cmd_args + 1, main);
			else
				execute_external_command(cmd, main);
			free(main->prompt);
			free_cmd(main->cmd);
			free(main->builtins);
			free_tab(main->env);
			free_local_env(&main->local_vars);
			exit(0);
		}
		waitpid(pid, &main->last_status, 0);
	}
	else if (i >= 0 && cmd->redir && !bi_has_output(i, cmd->cmd_args + 1))
		main->builtins[i].cmd(cmd->cmd_args + 1, main);
}

void	exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	pid_t	pid;
	int		pipefd[2];

	while (cmds)
	{
		create_pipe_and_fork(cmds, main, prev_pipe, pipefd, &pid);
		if (pid > 0)
		{
			close(pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			prev_pipe = pipefd[0];
			cmds = cmds->next;
		}
	}
	waitpid(pid, &main->last_status, 0);
	if (prev_pipe != -1)
		close(prev_pipe);
}
