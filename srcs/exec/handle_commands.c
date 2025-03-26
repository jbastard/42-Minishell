/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 07:57:06 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/26 07:57:06 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handle_commands.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jbastard <jbastard@student.1337.ma>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/18 08:03:13 by jbastard		  #+#	#+#			 */
/*   Updated: 2025/03/20 14:24:50 by jbastard		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_commands(t_minishell *main)
// {
// 	int		i;
// 	pid_t	pid;

// 	i = is_builtin(main->builtins, main->args[0]);
// 	if (i >= 0)
// 		main->builtins[i].cmd(args + 1, main);
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			perror("fork");
// 		else if (pid == 0)
// 		{
// 			if (execvp(args[0], args) == -1)
// 				perror("execve");
// 		}
// 		else
// 			waitpid(pid, &i, 0);
// 	}
// }

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
	int count;
	
	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	execute_external_command(t_cmd *cmd, t_minishell *main)
{
	if (execve(cmd->path, cmd->cmd_args, main->env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	exec_one_cmd(t_cmd *cmd, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, cmd->cmd_args[0]);
//	if (i >= 0 && bi_needs_child(i))
//		main->builtins[i].cmd(cmd->cmd_args + 1, main);
//	else
//	{
		pid = fork();
		if (pid == 0)
		{
			handle_redir(main, cmd);
			if (i > 0)
				main->builtins[i].cmd(cmd->cmd_args + 1, main);
			else
				execute_external_command(cmd, main);
		}
		else
			waitpid(pid, &main->last_status, 0);
//	}
}

void exec_multiple_cmds(t_cmd *cmds, t_minishell *main, int prev_pipe)
{
	pid_t pid;
	int pipefd[2];

	while (cmds)
	{
		if (cmds->next && pipe(pipefd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == 0)
		{
			if (prev_pipe != -1)
				dup2(prev_pipe, STDIN_FILENO);
			if (cmds->next)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			exec_one_cmd(cmds, main);
			exit(0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &main->last_status, 0);
			close(pipefd[1]);
			if (prev_pipe != -1)
				close(prev_pipe);
			prev_pipe = pipefd[0];
			cmds = cmds->next;
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}
	if (prev_pipe != -1)
		close(prev_pipe);
}

void	handle_commands(t_cmd *cmds, t_minishell *main)
{
	int cmd_count;
	int	prev_pipe;
	
	prev_pipe = -1;
	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
		exec_one_cmd(cmds, main);
	else
		exec_multiple_cmds(cmds, main, prev_pipe);
}

// void	print_parse(t_cmd	*cmd)
// {
// 	int		i;
// 	t_cmd	*tmp;
// 	t_redir	*tmpred;

// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->cmd_args[i])
// 			printf("Argument:   | %s\n", tmp->cmd_args[i++]);
// 		tmpred = tmp->redir;
// 		while (tmpred)
// 		{
// 			printf("Redir type: | %d\n", tmpred->type);
// 			printf("Redir file: | %s\n", tmpred->file);
// 			tmpred = tmpred->next;
// 		}
// 		printf("-----------------------\n");
// 		tmp = tmp->next;
// 	}
// }