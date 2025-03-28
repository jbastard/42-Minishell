/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 09:34:44 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	const char  *type_str;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			type_str = "WORD";
		else if (tokens->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (tokens->type == TOKEN_REDIR_IN)
			type_str = "REDIRECTION_IN";
		else if (tokens->type == TOKEN_REDIR_OUT)
			type_str = "REDIRECTION_OUT";
		else if (tokens->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else if (tokens->type == TOKEN_APPEND)
			type_str = "APPEND";
		printf("Token: %-20s | Type: %s\n", tokens->value, type_str);
		tokens = tokens->next;
	}
}

void	print_parse(t_cmd	*cmd)
{
	int		i;
	t_cmd	*tmp;
	t_redir	*tmpred;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_args[i])
			printf("Argument:   | %s\n", tmp->cmd_args[i++]);
		tmpred = tmp->redir;
		while (tmpred)
		{
			printf("Redir type: | %d\n", tmpred->type);
			printf("Redir file: | %s\n", tmpred->file);
			tmpred = tmpred->next;
		}
		printf("-----------------------\n");
		tmp = tmp->next;
	}
}

int handle_inputs(t_minishell *main)
{
	if (!main->is_here)
		main->line = readline(main->prompt);
	if (!main->line)
		return (free(main->line), 0);
	add_history(main->line);
	if (!get_cmd(main))
		return (free(main->line), 0);
	handle_commands(main->cmd, main);
	free_cmd(main->cmd);
	if (main->line)
		return (free(main->line), 1);
	return (1);
}

int	main()
{
	t_minishell	main;

	main = init_minishell();
	while(1)
	{
		set_sig_interactive();
		update_prompt(&main);
		if (!handle_inputs(&main))
			break ;
	}
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	free_local_env(&main.local_vars);
	rl_clear_history();
}
