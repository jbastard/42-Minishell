/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:24:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/14 15:48:55 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redir(t_redir **head, int type, char *file)
{
	t_redir	*tmp;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	new->file = strdup(file);
	new->type = type;
	new->next = NULL;
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

int	parse_cmd_into_tokens(t_cmd *cmd, t_token **toks)
{
	t_token	*curr;
	int		i;

	curr = *toks;
	i = 0;
	while (curr && curr->type != TOKEN_PIPE)
	{
		if (is_redir(curr))
		{
			if (!curr->next || curr->next->type != TOKEN_WORD)
				return (0);
			add_redir(&(cmd->redir), curr->type, curr->next->value);
			curr = curr->next->next;
		}
		else if (curr->type == TOKEN_WORD)
		{
			cmd->cmd_args[i] = ft_strdup(curr->value);
			if (!cmd->cmd_args[i])
				return (0);
			i++;
			curr = curr->next;
		}
	}
	*toks = curr;
	return (1);
}

t_cmd	*create_cmd(t_token **toks)
{
	t_cmd	*new;
	int		argcount;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	init_cmd(new);
	argcount = args_count(*toks);
	if (argcount == 0)
		return (free_cmd(new), NULL);
	if (!alloc_args(new, argcount))
		return (free_cmd(new), NULL);
	if (!parse_cmd_into_tokens(new, toks))
		return (free_cmd(new), NULL);
	return (new);
}

t_cmd	*parse_tokens(t_minishell *main)
{
	t_cmd	*cmds;
	t_token	*toks;

	cmds = NULL;
	toks = main->tokens;
	while (toks)
	{
		if (!add_cmds(&cmds, &toks))
			return (NULL);
		if (toks && toks->type == TOKEN_PIPE)
			toks = toks->next;
	}
	return (cmds);
}

char	*get_cmd(t_minishell *main, char *line)
{
	main->line = line;
	main->tokens = lexer(line, main);
	print_tokens(main->tokens);
	if (!main->tokens)
		return (NULL);
	else if (syntax_checker(main))
		return (free_lexer(main->tokens), NULL);
	main->cmd = parse_tokens(main);
	if (!main->cmd)
		return (free_lexer(main->tokens), NULL);
	return (free_lexer(main->tokens), line);
}
