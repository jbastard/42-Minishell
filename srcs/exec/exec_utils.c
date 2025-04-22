/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:58:04 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/15 09:52:03 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_builtin *builtins, char *cmd)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (!ft_strncmp(builtins[i].cmd_name, cmd, ft_strlen(cmd) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int	count_commands(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	exec_pipe_child(t_cmd *cmd,
						t_minishell *main,
						int prev_pipe,
						int pipefd[2])
{
	int		i;
	int		j;

	if (prev_pipe != -1)
		dup2(prev_pipe, STDIN_FILENO);
	if (cmd->next)
		dup2(pipefd[1], STDOUT_FILENO);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd->next)
		close(pipefd[1]);
	if (cmd->next)
		close(pipefd[0]);
	handle_redir(main, cmd);
	i = is_builtin(main->builtins, cmd->cmd_args[0]);
	if (i >= 0)
	{
		j = main->builtins[i].cmd(cmd->cmd_args + 1, main);
		free_all(main);
		exit(j);
	}
	execute_external_command(cmd, main);
	exit(main->last_status);
}

void	create_pipe_and_fork(t_cmd *cmd,
							t_minishell *main,
							int prev_pipe,
							int pipefd[2])
{
	cmd->pid = -1;
	if (cmd->next && pipe(pipefd) == -1)
		perror("pipe");
	cmd->pid = fork();
	if (cmd->pid == 0)
		exec_pipe_child(cmd, main, prev_pipe, pipefd);
	else if (cmd->pid > 0)
	{
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmd->next)
			close(pipefd[1]);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}

void	execute_external_command(t_cmd *cmd, t_minishell *main)
{
	if (!cmd->path)
	{
		ft_dprintf(2, "%s: command not found\n", cmd->cmd_args[0]);
		exit(127);
	}
	if (execve(cmd->path, cmd->cmd_args, main->env) == -1)
	{
		perror("execve");
		exit(1);
	}
}
