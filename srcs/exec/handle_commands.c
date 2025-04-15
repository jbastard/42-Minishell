/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:58:04 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/15 09:52:03 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handle_commands.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jbastard <jbastard@student.1337.ma>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/26 07:57:06 by jbastard		  #+#	#+#			 */
/*   Updated: 2025/03/26 07:57:06 by jbastard		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_commands(t_cmd *cmds, t_minishell *main)
{
	int	cmd_count;
	int	prev_pipe;
	
	prev_pipe = -1;
	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
		exec_one_cmd(cmds, main);
	else
		exec_multiple_cmds(cmds, main, prev_pipe);
}

int	bi_has_output(int i, char **args)
{
	if (i == 0 || i == 2 || (i == 3 && !*args) || i == 5 || i == 7)
	{
		printf("test\n");
		return (1);
	}
	return (0);
}

void	exec_one_cmd(t_cmd *cmd, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, cmd->cmd_args[0]);
	if (i >= 0 && (bi_has_output(i, cmd->cmd_args + 1) || !cmd->redir))
		main->builtins[i].cmd(cmd->cmd_args + 1, main);
	if (i < 0 || cmd->redir)
	{
		pid = fork();
		if (pid == 0)
		{
			if (prepare_heredocs(cmd, main))
				exit(1);
			handle_redir(main, cmd);
			if (i >= 0)
				main->builtins[i].cmd(cmd->cmd_args + 1, main);
			else
				execute_external_command(cmd, main);
			exit(0);
		}
		else
			waitpid(pid, &main->last_status, 0);
	}
	if (i >= 0 && !cmd->redir)
		main->builtins[i].cmd(cmd->cmd_args + 1, main);
//	else if (i >= 0 && cmd->redir && !bi_has_output(i, cmd->cmd_args + 1))
//		main->builtins[i].cmd(cmd->cmd_args + 1, main);
}

void	exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	pid_t pid;
	int pipefd[2];

	while (cmds)
	{
		if (prepare_heredocs(cmds, main))
			exit(1);
		create_pipe_and_fork(cmds, main, prev_pipe, pipefd, &pid);
		if (pid > 0)
		{
			waitpid(pid, &main->last_status, 0);
			close(pipefd[1]);
			if (prev_pipe != -1)
	   			close(prev_pipe);
   			prev_pipe = pipefd[0];
			cmds = cmds->next;
		}
	}
	if (prev_pipe != -1)
		close(prev_pipe);
}
