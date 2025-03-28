/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:50:58 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 11:08:19 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_var(t_lexer *lexer, t_minishell *main, char *env_value, int k)
{
	env_value = ft_itoa(main->last_status);
	k = 0;
	while (env_value[k])
		lexer->buffer[lexer->j++] = env_value[k++];
	free(env_value);
	lexer->i++;
}

void	generic_var(t_lexer *lexer, t_minishell *main, char *env_value, int k)
{
	char	var_name[1024];

	k = 0;
	while (ft_isalnum(lexer->input[lexer->i])
		|| lexer->input[lexer->i] == '_')
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

void	handle_env_var(t_lexer *lexer, t_minishell *main)
{
	char	*env_value;
	int		k;

	k = 0;
	lexer->i++;
	env_value = NULL;
	if (lexer->input[lexer->i] == '?')
		error_var(lexer, main, env_value, k);
	else if (ft_isalpha(lexer->input[lexer->i])
		|| lexer->input[lexer->i] == '_')
		generic_var(lexer, main, env_value, k);
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
