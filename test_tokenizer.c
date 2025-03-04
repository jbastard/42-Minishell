/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:22:52 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/04 09:58:00 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/includes/minishell.h"

#define TOKEN_WORD 1
#define TOKEN_PIPE 2
#define TOKEN_REDIR 3
#define TOKEN_ENV_VAR 4
#define TOKEN_HEREDOC 5
#define TOKEN_APPEND  6
#define TOKEN_SINGLE_QUOTED 7
#define TOKEN_DOUBLE_QUOTED 8
#define TOKEN_SEMICOLON 9

typedef struct s_token
{
	char            *value;
	int             type;
	struct s_token  *next;
}               t_token;

typedef struct s_lexer
{
	const char  *input;
	t_token     *tokens;
	char        buffer[1024];
	int         i;
	int         j;
	char        quote;
} t_lexer;

//ATTENTION AUCUNE GESTION DES ERREURS
//new_token

//handle_env_var : si aucun charactere valide n est derriere le $ le token est constitue uniquement de $
//a verifier dans le parsing

int is_whitespaces(char c)
{
	return (c <= 32);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

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

///@brief Objectif est d indentifier les variables d environnement pour les traiter plus tard
///On ajoute $ au buffer puis on recupere les charactere suivant (alnum ou _) pour les ajouter au buffer
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
	lexer->buffer[lexer->j] = '\0';
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
		ft_dprintf(STDERR_FILENO, "Appliquer la gestion d erreur pour les d_quotes non fermees\n");
	else
		lexer->i++;
	lexer->buffer[lexer->j] = '\0';
	add_token(&(lexer->tokens), lexer->buffer, TOKEN_WORD);
	lexer->j = 0;
}

///@brief de la meme maniere que pour les simples on rempli le buffer avec le contenu entre les quotes
/// Ici on traite les variables d environnement (comme en bash) en l identifiant avec le $ elles sont directement
/// traduites et ajoutee
void 	handle_double_quotes(t_lexer *lexer)
{
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\"')
	{
		if (lexer->input[lexer->i] == '$')
			handle_env_var(lexer);
		else
			lexer->buffer[lexer->j++] = lexer->input[lexer->i];
		lexer->i++;
	}
	if (lexer->input[lexer->i] != '\"')
		ft_dprintf(STDERR_FILENO, "Appliquer la gestion d erreur pour les d_quotes non fermees\n");
	else
		lexer->i++;
	lexer->buffer[lexer->j] = '\0';
	add_token(&(lexer->tokens), lexer->buffer, TOKEN_DOUBLE_QUOTED);
	lexer->j = 0;
}

///@brief On rempli un token avec le contenu du buffer avant le charactere special
/// ensuite on place le charactere dans un token separe
void 	handle_special_char(t_lexer *lexer)
{
	if (lexer->j > 0)
	{
		lexer->buffer[lexer->j] = '\0';
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_WORD);
		lexer->j = 0;
	}
	lexer->buffer[0] = lexer->input[lexer->i];
	lexer->buffer[1] = '\0';
	if (lexer->input[lexer->i] == ';')
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_SEMICOLON);
	else if (lexer->input[lexer->i] == '|')
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_PIPE);
	else
		add_token(&(lexer->tokens), lexer->buffer, TOKEN_REDIR);
}

///@brief L objectif est de gerer les heredoc et les append, pour cela on recupere la charactere special et
/// si le charactere suivant n est pas le meme on traite le char actuel comme une redirection on le stock dans le buffer
void handle_double_char_op(t_lexer *lexer)
{
	char	c = lexer->input[lexer->i];
	char 	buffer[3];

	buffer[0] = c;
	if (lexer->input[lexer->i + 1] == c)
	{
		buffer[1] = c;
		buffer[2] = '\0';
		lexer->i++;
		if (lexer->input[lexer->i] == '<')
			add_token(&(lexer->tokens), buffer, TOKEN_HEREDOC);
		else
			add_token(&(lexer->tokens), buffer, TOKEN_APPEND);
	}
	else
	{
		buffer[1] = '\0';
		add_token(&(lexer->tokens), buffer, TOKEN_REDIR);
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