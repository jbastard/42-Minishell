/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:35:52 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/04 10:38:13 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

///attention comportement bizzard avec les messages d erreur jai pas encore compris pourquoi
/// il faut les gerer pour exit en cas d erreur je pense que ca suffit

///@brief Allocation et initialisation d un nouveau token
///@param value Correspond a la valeur du token
///@param type Correspond au type de token (TOKEN_PIPE / TOKEN_REDIR /...)
t_token *new_token(char *value, int type)
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

///@brief Ajout d'un nouveau token a la fin de la liste chainee
/// si celle-ci est vide le nouveau token devient la tete de liste
///@param head un pointeur vers la tete de liste
/// on recupere @param value et @param type pour les envoyer dans new_token
void 	add_token(t_token **head, char *value, int type)
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

///@brief remplir le token avec du texte apres avoir check tout les autres cas
void handle_buffer(t_lexer	*lexer)
{
	if (lexer->j > 0)
	{
		lexer->buffer[lexer->j] = '\0';
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_WORD);
		lexer->j = 0;
	}
}

void init_lexer(t_lexer *lexer, const char *input)
{
	lexer->input = input;
	lexer->tokens = NULL;
	lexer->i = 0;
	lexer->j = 0;
	lexer->quote = 0;
}

t_token	*lexer(char *input)
{
	t_lexer lexer;

	init_lexer(&lexer, input);
	while (lexer.input[lexer.i])
	{
		if (is_whitespaces(lexer.input[lexer.i]) && !lexer.quote)
			handle_buffer(&lexer);
		else if (lexer.input[lexer.i] == '\'')
			handle_single_quotes(&lexer);
		else if (lexer.input[lexer.i] == '\"')
			handle_double_quotes(&lexer);
		else if ((lexer.input[lexer.i] == '<'
			  || lexer.input[lexer.i] == '>') && !lexer.quote)
			handle_double_char_op(&lexer);
		else if (is_special_char(lexer.input[lexer.i]) && !lexer.quote)
			handle_special_char(&lexer);
		else if (lexer.input[lexer.i] == '$' && !lexer.quote)
			handle_env_var(&lexer);
		else
			lexer.buffer[lexer.j++] = lexer.input[lexer.i];
		lexer.i++;
	}
	handle_buffer(&lexer);
	return (lexer.tokens);
}