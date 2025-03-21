/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:35:52 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/20 10:59:22 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), NULL);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, char *value, int type)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(value, type);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_buffer(t_lexer	*lexer)
{
	if (lexer->j > 0)
	{
		lexer->buffer[lexer->j] = '\0';
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_WORD);
		lexer->j = 0;
	}
}

void	add_redirection_token(t_lexer *lexer, char c)
{
	char	buffer[3];

	buffer[0] = c;
	buffer[1] = '\0';
	buffer[2] = '\0';
	if (lexer->input[lexer->i + 1] == c)
	{
		add_double_token(lexer, c);
		lexer->i++;
	}
	else if (c == '>')
		add_token(&(lexer->tokens), buffer, TOKEN_REDIR_OUT);
	else if (c == '<')
		add_token(&(lexer->tokens), buffer, TOKEN_REDIR_IN);
	else if (c == '|')
		add_token(&(lexer->tokens), buffer, TOKEN_PIPE);
}

t_token	*lexer(char *line, t_minishell *main)
{
	t_lexer	lexer;

	init_lexer(&lexer, line);
	while ((size_t)lexer.i < lexer.input_len)
	{
		if (lexer.input[lexer.i] == '\'')
			handle_single_quotes(&lexer);
		else if (lexer.input[lexer.i] == '\"')
			handle_double_quotes(&lexer);
		else if (is_special_char(lexer.input[lexer.i]) && !lexer.quote)
			handle_special_char_op(&lexer);
		else if (lexer.input[lexer.i] == '$' && !lexer.quote)
			handle_env_var(&lexer);
		else if (is_whitespaces(lexer.input[lexer.i]) && !lexer.quote)
			handle_buffer(&lexer);
		else if (!is_whitespaces(lexer.input[lexer.i]) && !lexer.quote)
			lexer.buffer[lexer.j++] = lexer.input[lexer.i];
		lexer.i++;
	}
	main->last_status = lexer.error;
	if (lexer.error)
		return (free_lexer(lexer.tokens), NULL);
	handle_buffer(&lexer);
	return (lexer.tokens);
}
