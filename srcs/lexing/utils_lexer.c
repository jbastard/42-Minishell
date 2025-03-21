/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:39:13 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/21 08:33:32 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_env_var(t_lexer *lexer)
{
	char	var_name[1024];
	char	*env_value;
	int		k;

	k = 0;
	lexer->i++;
	if (lexer->input[lexer->i] == '?')
	{
		lexer->buffer[lexer->j++] = '$';
		lexer->buffer[lexer->j++] = '?';
		lexer->buffer[lexer->j++] = '\0';
	}
	else
	{
		while (ft_isalnum(lexer->input[lexer->i])
			|| lexer->input[lexer->i] == '_')
			var_name[k++] = lexer->input[lexer->i++];
		var_name[k] = '\0';
		env_value = getenv(var_name);
		if (env_value)
			while (*env_value)
				lexer->buffer[lexer->j++] = *env_value++;
	}
}

void	handle_single_quotes(t_lexer *lexer)
{
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\'')
		lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	if (lexer->input[lexer->i] != '\'')
	{
		ft_dprintf(2, "minihell: syntax error: unclosed single quote\n");
		lexer->error = 2;
		return ;
	}
	lexer->i++;
	while (!is_whitespaces(lexer->input[lexer->i]))
		lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	handle_buffer(lexer);
}

void	handle_double_quotes(t_lexer *lexer)
{
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\"')
	{
		if (lexer->input[lexer->i] == '$')
			handle_env_var(lexer);
		else
			lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	}
	if (lexer->input[lexer->i] != '\"')
	{
		ft_dprintf(2, "minihell: syntax error: unclosed double quote\n");
		lexer->error = 2;
		return ;
	}
	lexer->i++;
	while (!is_whitespaces(lexer->input[lexer->i]))
		lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	handle_buffer(lexer);
}

void	add_double_token(t_lexer *lexer, char c)
{
	if (c == '<')
		add_token(&(lexer->tokens), "<<", TOKEN_HEREDOC);
	else if (c == '>')
		add_token(&(lexer->tokens), ">>", TOKEN_APPEND);
	else if (c == '|')
	{
		add_token(&(lexer->tokens), "|", TOKEN_PIPE);
		add_token(&(lexer->tokens), "|", TOKEN_PIPE);
	}
}

void	handle_special_char_op(t_lexer *lexer)
{
	char	c;

	if (lexer->j > 0)
		handle_buffer(lexer);
	c = lexer->input[lexer->i];
	add_redirection_token(lexer, c);
}
