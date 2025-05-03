/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:57:33 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/03 13:57:37 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_var(t_lexer *lexer, t_minishell *main)
{
	char	*str;
	int		k;

	str = ft_itoa(main->last_status);
	if (!str)
		return ;
	k = 0;
	while (str[k] && lexer->j < BUFFER_SIZE - 1)
		lexer->buffer[lexer->j++] = str[k++];
	free(str);
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
		error_var(lexer, main);
	else if (ft_isalpha(lexer->input[lexer->i])
		|| lexer->input[lexer->i] == '_')
		generic_var(lexer, main, env_value, k);
	else
		lexer->buffer[lexer->j++] = '$';
}
