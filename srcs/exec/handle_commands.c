/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:58:04 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/25 11:40:51 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		no_args_redirs(t_minishell main)
{
	t_cmd *cmds = main.cmd;
	int		fd;

	cmds = main.cmd;
	fd = 0;
	while (cmds)
	{
		if (!cmds->cmd_args && cmds->redir && (cmds->redir->type == TOKEN_REDIR_OUT || cmds->redir->type == TOKEN_APPEND))
			fd = open(cmds->redir->file, O_CREAT, 0777);
		cmds = cmds->next;
		if (fd)
			close(fd);
	}
}

void	handle_commands(t_cmd *cmds, t_minishell *main)
{
	int	cmd_count;
	int	prev_pipe;

	prev_pipe = -1;
	cmd_count = count_commands(cmds);
	preprocess_heredocs(main, main->cmd);
	no_args_redirs(*main);
	if (main->cmd->cmd_args && cmd_count == 1)
	{
		if (exec_one_cmd(cmds, main) == 127)
			main->last_status = 127;
	}
	else if (main->cmd->cmd_args)
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
	signal(SIGQUIT, SIG_DFL);
	execute_external_command(cmd, main);
	signal(SIGQUIT, SIG_IGN);
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
	if (!cmd->path && ft_strncmp(cmd->cmd_args[0], "mordex", 7))
		return (ft_dprintf(2, "%s%s", cmd->cmd_args[0], CNT), 127);
	if ((i < 0 || cmd->redir) && bi_has_output(i, cmd->cmd_args + 1))
	{
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
		if (!cmds->cmd_args)
		{
			cmds = cmds->next ;
			j = 126;
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
	if (j != 127 && j != 126)
		waitpid(cmds->pid, &main->last_status, 0);
	if (WIFEXITED(main->last_status) && j != 127)
		main->last_status = WEXITSTATUS(main->last_status);
	else if (WIFSIGNALED(main->last_status) && j != 127)
		main->last_status = 128 + WTERMSIG(main->last_status);
	if (prev_pipe != -1 && j != 127)
		close(prev_pipe);
}
