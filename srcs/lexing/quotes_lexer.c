/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:50:58 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/28 09:18:42 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_single_quotes(t_lexer *lexer)
{
	int	start;

	start = lexer->j;
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\''
		&& lexer->j < BUFFER_SIZE - 1)
		lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	if (lexer->input[lexer->i] != '\'')
	{
		ft_dprintf(2, "minishell: syntax error: unclosed single quote\n");
		lexer->error = 2;
		lexer->i = (int)lexer->input_len;
		return (0);
	}
	lexer->i++;
	if (lexer->j == start)
		lexer->force_token = 1;
	return (1);
}

int	double_quote_error(t_lexer	*lexer)
{
	ft_dprintf(2, "minishell: syntax error: unclosed double quote\n");
	lexer->error = 2;
	lexer->i = (int)lexer->input_len;
	return (0);
}

int	handle_double_quotes(t_lexer *lexer, t_minishell *main)
{
	int	start;

	start = lexer->j;
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\"'
		&& lexer->j < BUFFER_SIZE - 1)
	{
		if (lexer->input[lexer->i] == '$'
			&& (ft_isalnum(lexer->input[lexer->i + 1])
				|| lexer->input[lexer->i + 1] == '_'
				|| lexer->input[lexer->i + 1] == '?'))
			handle_env_var(lexer, main);
		else
			lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	}
	if (lexer->input[lexer->i] != '\"')
		return (double_quote_error(lexer));
	lexer->i++;
	if (lexer->j == start)
		lexer->force_token = 1;
	return (1);
}
