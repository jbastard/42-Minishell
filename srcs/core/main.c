/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/08 15:19:08 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_tokens(t_token *tokens)
{
	const char  *type_str;

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
		else if (tokens->type == TOKEN_SINGLE_QUOTED)
			type_str = "SINGLE_QUOTED";
		else if (tokens->type == TOKEN_DOUBLE_QUOTED)
			type_str = "DOUBLE_QUOTED";
		else if (tokens->type == TOKEN_SEMICOLON)
			type_str = "SEMICOLON";
		else
			type_str = "UNKNOWN";
		printf("Token: %-10s | Type: %s\n", tokens->value, type_str);
		tokens = tokens->next;
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
		line = get_cmd(&main);
		if (!line)
			break ;
		if (line[0] != 0)
		{
			add_history(line);
			main.tokens = lexer(line);
			print_tokens(main.tokens);
			temp = ft_split(line, ' ');
			handle_commands(temp, &main);
			free_tab(temp);
			if (main.tokens)
				free_lexer(main.tokens);
			free(line);
		}
	}
	free(line);
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	rl_clear_history();
}
