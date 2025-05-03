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

char	*ft_getenv(char *name, t_minishell *main)
{
	int		i;
	int		len;

	if (!main || !main->env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (main->env[i])
	{
		if (!ft_strncmp(main->env[i], name, len)
			&& main->env[i][len] == '=')
			return (main->env[i]);
		i++;
	}
	return (NULL);
}

int	get_equals(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (-1);
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
