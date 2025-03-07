/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:39:13 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/06 17:12:31 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_env_var(t_lexer *lexer)
{
	char	var_name[1024];
	char 	*env_value;
	int		k;

	k = 0;
	lexer->i++;
	if (ft_isdigit(lexer->input[lexer->i] || lexer->input[lexer->i] == '?'))
		var_name[k++] = lexer->input[lexer->i++];
	else
		while (ft_isalnum(lexer->input[lexer->i])
			   || lexer->input[lexer->i] == ' ')
			var_name[k++] = lexer->input[lexer->i++];
	var_name[k] = '\0';
	env_value = getenv(var_name);
	if (env_value)
		while (*env_value)
			lexer->buffer[lexer->j++] = *env_value++;
}

///@brief On traite ici les single quotes on rempli le buffer
/// avec tout les charactere qui suivent la quote jusqu a celle d apres
/// on saute la quote d ouverture et de fermeture
void 	handle_single_quotes(t_lexer *lexer)
{
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\'')
		lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	if (lexer->input[lexer->i] != '\'')
		printf("Appliquer la gestion d erreur pour les s_quotes non fermees\n");
//	else
//		lexer->i++;
	lexer->buffer[lexer->j] = '\0';
	add_token(&(lexer->tokens), lexer->buffer, TOKEN_WORD);
	lexer->j = 0;
}

///@brief de la meme maniere que pour les simples on rempli le buffer avec le contenu entre les quotes
/// Ici on traite les variables d environnement (comme en bash) en l identifiant avec le $ elles sont directement
/// traduites et ajoutee
void handle_double_quotes(t_lexer *lexer)
{
	lexer->i++;
	while (lexer->input[lexer->i])
	{
		if (lexer->input[lexer->i] == '\"')
			return;
		else if (lexer->input[lexer->i] == '$')
			handle_env_var(lexer);
		else
			lexer->buffer[lexer->j++] = lexer->input[lexer->i++];
	}
	fprintf(stderr, "Quotes non fermees, mettre un msg d erreur\n");
}

int 	is_multiple_chars(t_lexer *lexer, const char *line, char c)
{
	int i;

	i = 0;
	while (line[i] == c)
		i++;
	if (i > 2)
	{
		if (i == 3)
			printf("minishell: syntax error near unexpected token `%c'\n", c);
		else
			printf("minishell: syntax "
				   "error near unexpected token `%c%c'\n", c, c);
		lexer->i += i;
		return (0);
	}
	return (1);
}

void 	add_redirection_token(t_lexer *lexer, char c)
{
	char buffer[3];

	buffer[0] = c;
	buffer[1] = '\0';
	buffer[2] = '\0';

	if (!is_multiple_chars(lexer, lexer->input, c))
		return ;
	if (lexer->input[lexer->i + 1] && lexer->input[lexer->i + 1] == c)
	{
		buffer[1] = c;
		lexer->i++;
		if (c == '<')
			add_token(&(lexer->tokens), buffer, TOKEN_HEREDOC);
		else if (c == '>')
			add_token(&(lexer->tokens), buffer, TOKEN_APPEND);
	}
	else
	{
		if (c == '<')
			add_token(&(lexer->tokens), buffer, TOKEN_REDIR_IN);
		else if (c == '>')
			add_token(&(lexer->tokens), buffer, TOKEN_REDIR_OUT);
		else if (c == '|')
			add_token(&(lexer->tokens), buffer, TOKEN_PIPE);
	}
}

///@brief L objectif est de gerer les heredoc et les append, pour cela on recupere la charactere special et
/// si le charactere suivant n est pas le meme on traite le char actuel comme une redirection on le stock dans le buffer
void handle_special_char_op(t_lexer *lexer)
{
	char	c;

	if (lexer->j > 0)
		handle_buffer(lexer);
	c = lexer->input[lexer->i];
	add_redirection_token(lexer, c);
}
