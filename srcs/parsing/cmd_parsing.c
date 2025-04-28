/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:15:14 by nlecreux          #+#    #+#             */
/*   Updated: 2025/04/25 11:03:05 by jbastard         ###   ########.fr       */
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
	new->is_heredoc_tmp = 0;
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
//	if (argcount == 0)
//		return (free_cmd(new), NULL);
	if (argcount && !alloc_args(new, argcount))
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

void	print_tokens(t_token *tokens)
{
	const char  *type_str;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			type_str = "WORD";
		else if (tokens->type == TOKEN_PIPE)
				type_str = "PIPE";
			else if (tokens->type == TOKEN_REDIR_IN)
					type_str = "REDIRECTION_IN";
				else if (tokens->type == TOKEN_REDIR_OUT)
						type_str = "REDIRECTION_OUT";
					else if (tokens->type == TOKEN_HEREDOC)
							type_str = "HEREDOC";
						else if (tokens->type == TOKEN_APPEND)
								type_str = "APPEND";
		printf("Token: %-20s | Type: %s\n", tokens->value, type_str);
		tokens = tokens->next;
	}
}

void	print_parse(t_cmd	*cmd)
{
	int		i;
	t_cmd	*tmp;
	t_redir	*tmpred;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_args[i])
			printf("Argument:   | %s\n", tmp->cmd_args[i++]);
		tmpred = tmp->redir;
		while (tmpred)
		{
			printf("Redir type: | %d\n", tmpred->type);
			printf("Redir file: | %s\n", tmpred->file);
			tmpred = tmpred->next;
		}
		printf("-----------------------\n");
		tmp = tmp->next;
	}
}

int	get_cmd(t_minishell *main)
{
	main->tokens = lexer(main->line, main);
	if (!main->tokens)
		return (0);
	if (!syntax_checker(main))
		return (free_lexer(main->tokens), 0);
	main->cmd = parse_tokens(main);
	if (!main->cmd)
		return (free_lexer(main->tokens), 0);
	if (check_cmd(main))
		return (free_lexer(main->tokens), free_cmd(main->cmd), 0);
	return (free_lexer(main->tokens), 1);
}
