/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexing_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:46:20 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/04 10:47:36 by jbastard         ###   ########.fr       */
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
		else if (tokens->type == 3)
			type_str = "REDIRECTION";
		else if (tokens->type == 4)
			type_str = "ENV_VAR";
		else if (tokens->type == 5)
			type_str = "HEREDOC";
		else if (tokens->type == 6)
			type_str = "APPEND";
		else if (tokens->type == TOKEN_SINGLE_QUOTED)
			type_str = "SINGLE_QUOTED";
		else if (tokens->type == TOKEN_DOUBLE_QUOTED)
			type_str = "DOUBLE_QUOTED";
		else
			type_str = "UNKNOWN";
		printf("Token: %-10s | Type: %s\n", tokens->value, type_str);
		tokens = tokens->next;
	}
}

int main(void)
{
	char    *input = "echo \'Path: $HOME\'";
	t_token *tokens = lexer(input);

	print_tokens(tokens);
	return (0);
}
