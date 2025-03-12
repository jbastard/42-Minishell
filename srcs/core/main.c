/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/12 11:49:27 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_tokens(t_token *tokens)
{
	const char  *type_str;

	if (tokens) {
		printf("error parsing");
		return;
	}
	while (tokens)
	{
		if (tokens->type == 1)
			type_str = "WORD";
		else if (tokens->type == 2)
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

void 	print_parse(t_cmd	*cmd)
{
	int i;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_args[i])
			printf("Argument:   | %s\n", cmd->cmd_args[i++]);
		while (cmd->redir)
		{
			printf("Redir type: | %d\n", cmd->redir->type);
			printf("Redir file: | %s\n", cmd->redir->file);
			cmd->redir = cmd->redir->next;
		}
		printf("-----------------------\n");
		cmd = cmd->next;
	}
}

int	main()
{
	char		*line;
	char		**temp;
	t_minishell	main;

	main = init_minishell();
	sig_handler();
	while(1)
	{
		update_prompt(&main);
		line = readline(main.prompt);
		if (!line)
			break ;
		if (line[0] != 0)
		{
			add_history(line);
			get_cmd(&main, line);
			print_tokens(main.tokens);
			print_parse(main.cmd);
			temp = ft_split(line, ' ');
			handle_commands(temp, &main);
			free_parser(&main);
			free_tab(temp);
			free(line);
		}
	}
	free(line);
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	rl_clear_history();
}
