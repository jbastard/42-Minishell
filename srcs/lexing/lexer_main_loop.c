/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:56:57 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/03 10:56:57 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_quotes(t_lexer *lx, t_minishell *ms)
{
	if (lx->input[lx->i] == '\'')
		return (handle_single_quotes(lx));
	if (lx->input[lx->i] == '\"')
		return (handle_double_quotes(lx, ms));
	return (1);
}

static int	handle_special(t_lexer *lx)
{
	if (is_special_char(lx->input[lx->i]))
	{
		handle_buffer(lx);
		handle_special_char_op(lx);
		return (1);
	}
	if (is_whitespaces(lx->input[lx->i]))
	{
		handle_buffer(lx);
		lx->i++;
		return (1);
	}
	return (0);
}

t_token	*lexer(char *line, t_minishell *main)
{
	t_lexer	lx;

	init_lexer(&lx, line);
	while ((size_t)lx.i < lx.input_len)
	{
		if (lx.input[lx.i] == '\'' || lx.input[lx.i] == '\"')
		{
			if (!handle_quotes(&lx, main))
				return (free_lexer(lx.tokens), NULL);
			continue ;
		}
		if (handle_special(&lx))
			continue ;
		if (lx.input[lx.i] == '$')
		{
			handle_env_var(&lx, main);
			continue ;
		}
		lx.buffer[lx.j++] = lx.input[lx.i++];
	}
	handle_buffer(&lx);
	return (lx.tokens);
}
