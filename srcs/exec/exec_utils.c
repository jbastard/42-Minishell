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

void	create_pipe_and_fork(t_cmd *cmds, t_minishell *main, int prev_pipe, int pipefd[2], int *pid)
{
	if (cmds->next && pipe(pipefd) == -1)
		perror("pipe");
	*pid = fork();
	if (*pid == 0)
	{
		if (prev_pipe != -1)
			dup2(prev_pipe, STDIN_FILENO);
		if (cmds->next)
			dup2(pipefd[1], STDOUT_FILENO);
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmds->next)
			close(pipefd[1]);
		if (cmds->next)
			close(pipefd[0]);
		g_signal = SIG_CHILD;
		exec_one_cmd(cmds, main);
		free(main->prompt);
		free_cmd(main->cmd);
		free(main->builtins);
		free_tab(main->env);
		free_local_env(&main->local_vars);
		exit(0);
	}
	else if (*pid > 0) {
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmds->next)
			close(pipefd[1]);
	}
	if (*pid < 0)
		return (perror("fork"), exit(1));
}

void	execute_external_command(t_cmd *cmd, t_minishell *main)
{
	if (!cmd->path)
	{
		ft_dprintf(2, "No such file or directory\n");
		exit(127);
	}
	if (execve(cmd->path, cmd->cmd_args, main->env) == -1)
	{
		perror("execve");
		exit(1);
	}
}
