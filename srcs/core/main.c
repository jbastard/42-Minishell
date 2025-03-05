/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/04 12:34:52 by jbastard         ###   ########.fr       */
=======
/*   Updated: 2025/03/04 15:10:06 by nlecreux         ###   ########.fr       */
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
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
	t_minishell	main;
<<<<<<< HEAD

=======
	char		**temp;
	
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
	main = init_minishell();
	sig_handler();
	while(1)
	{
		line = get_cmd(&main);
		if (!line) {
			break ;
<<<<<<< HEAD
		}
		if (line[0] != 0) {
			add_history(line);
		}

		/// l output du lexer renvoie donc une pointeur vers la liste chainee comprenant chaque token, on doit
		/// integrer le parsing pour recuperer et comparer les commande pour reagir en consequences.
		main.tokens = lexer(line);
		print_tokens(main.tokens);

//		handle_commands(ft_split(line, ' '), &main);
		free(line);
=======
		if (line[0] != 0)
		{
			add_history(line);
			temp = ft_split(line, ' ');
			handle_commands(temp, &main);
			free_tab(temp);
			free(line);
		}
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
	}
	free(line);
	free(main.prompt);
	free(main.builtins);
	free_tab(main.env);
	rl_clear_history();
}
