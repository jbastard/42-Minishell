/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:35:52 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/14 10:16:39 by jbastard         ###   ########.fr       */
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

void	init_lexer(t_lexer *lexer, const char *input)
{
	lexer->input = input;
	lexer->input_len = ft_strlen(input);
	lexer->tokens = NULL;
	lexer->i = 0;
	lexer->j = 0;
	lexer->quote = 0;
	lexer->error = 0;
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

void	free_lexer(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->value)
			free(token->value);
		temp = token;
		token = token->next;
		free(temp);
	}
	token = NULL;
}
