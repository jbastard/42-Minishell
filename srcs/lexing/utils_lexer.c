/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:39:13 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/26 14:36:09 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *env, t_minishell *main)
{
	int	i;
	int	j;

	i = 0;
	while (main->env[i])
	{
		j = len_equal(main->env[i]);
		if (j < len_equal(env))
			j = len_equal(env);
		if (!ft_strncmp(env, main->env[i], j))
			return (main->env[i]);
		i++;
	}
	return (NULL);
}

int		get_equals(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

void	handle_env_var(t_lexer *lexer, t_minishell *main)
{
	char	var_name[1024];
	char	*env_value;
	int		k;

	lexer->i++;
	if (lexer->input[lexer->i] == '?')
	{
		env_value = ft_itoa(main->last_status);
		k = 0;
		while (env_value[k])
			lexer->buffer[lexer->j++] = env_value[k++];
		free(env_value);
		lexer->i++;
	}
	else if (ft_isalpha(lexer->input[lexer->i]) || lexer->input[lexer->i] == '_')
	{
		k = 0;
		while (ft_isalnum(lexer->input[lexer->i]) || lexer->input[lexer->i] == '_')
			var_name[k++] = lexer->input[lexer->i++];
		var_name[k] = '\0';
		env_value = ft_getenv(var_name, main);
		if (env_value)
		{
			env_value += get_equals(env_value);
			k = 0;
			while (env_value[k])
				lexer->buffer[lexer->j++] = env_value[k++];
		}
	}
	else
		lexer->buffer[lexer->j++] = '$';
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

void	handle_double_quotes(t_lexer *lexer, t_minishell *main)
{
	lexer->i++;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\"')
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
