/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handle_commands.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nlecreux <nlecreux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/25 16:39:38 by nlecreux		  #+#	#+#			 */
/*   Updated: 2025/03/10 17:25:58 by nlecreux		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_commands(char **args, t_minishell *main)
{
	int		i;
	pid_t	pid;

	i = is_builtin(main->builtins, args[0]);
	if (i >= 0)
		main->builtins[i].cmd(args + 1, main);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("execve");
		}
		else
			waitpid(pid, &i, 0);
	}
}

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

// void	execute_external_command(t_minishell *main, int input_fd, int output_fd)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (input_fd != -1)
// 		{
// 			dup2(input_fd, STDIN_FILENO);
// 			close(input_fd);
// 		}
// 		if (output_fd != -1)
// 		{
// 			dup2(output_fd, STDOUT_FILENO);
// 			close(output_fd);
// 		}
// 		if (execve(main->cmd.path, main->cmd.args, main->env) == -1)
// 			perror("execve");
// 		exit(1);
// 	}
// 	return (pid);
// }

// int	count_commands(t_cmd *cmds)
// {
// 	int count;
	
// 	count = 0;
// 	while (cmds)
// 	{
// 		count++;
// 		cmds = cmds->next;
// 	}
// 	return (count);
// }

// void	handle_commands(t_cmd *cmds, t_minishell *main)
// {
// 	int pipefd[2];
// 	int	prev_pipe;
// 	int cmd_count;
// 	int i;
	
// 	prev_pipe = -1;
// 	cmd_count = count_commands(cmds);
// 	while (cmds)
// 	{
// 		if (cmds->next && pipe(pipefd) == -1)
// 			perror("pipe");
// 		i = is_builtin(main->builtins, cmds->cmd_args[0]);
// 		if (i >= 0)
// 			main->status = main->builtins[i].cmd(cmds->args + 1, main);
// 		else
// 			execute_external_command(main, pipefd, prev_pipe, cmd_count);
// 		if (prev_pipe != -1)
// 			close(prev_pipe);
// 		if (cmds->next)
// 			close(pipefd[1]);
// 		prev_pipe = pipefd[0];
// 		cmds = cmds->next;
// 	}
// 	if (prev_pipe != -1)
// 		close(prev_pipe);
// }
