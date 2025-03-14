/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:39:57 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/14 15:52:20 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes(t_minishell *main)
{
	t_token	*toks;

	toks = main->tokens;
	if (toks->type == TOKEN_PIPE
		&& (!toks->next
			|| toks->next->type == TOKEN_PIPE))
	{
		ft_dprintf(STDOUT_FILENO, "minihell: "
			"syntax error: invalid pipe\n");
		return (ERR_SYNTAX);
	}
	return (0);
}

int	check_redirs(t_minishell *main)
{
	t_token	*toks;

	toks = main->tokens;
	if (!toks->next && is_redir(toks))
		return (handle_error(main, ERR_SYNTAX, "newline"));
	else if (toks->next
		&& toks->next->type != TOKEN_WORD
		&& is_redir(toks))
	{
		if (toks->next->type == TOKEN_PIPE)
			return (handle_error(main, ERR_SYNTAX, "|"));
		else
			return (handle_error(main, ERR_SYNTAX, toks->next->value));
	}
	return (0);
}

int	syntax_checker(t_minishell *main)
{
	t_minishell	minishell;

	minishell.tokens = main->tokens;
	if (minishell.tokens->type == TOKEN_PIPE)
		return (handle_error(main, ERR_SYNTAX, "|"));
	while (minishell.tokens)
	{
		if (check_redirs(&minishell))
			return (1);
		if (check_pipes(&minishell))
			return (1);
		minishell.tokens = minishell.tokens->next;
	}
	return (0);
}
