/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:24:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/13 11:39:40 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	init_cmd(t_cmd *new)
{
	new->redir = NULL;
	new->next = NULL;
	new->cmd_args = NULL;
	new->path = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
}

int		is_redir(t_token *toks)
{
	if (toks->type != TOKEN_PIPE && toks->type != TOKEN_WORD)
		return (1);
	return (0);
}

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

int 	args_count(t_token *toks)
{
	int count;
	t_token	*tmp;

	count = 0;
	tmp = toks;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
				return(0);
			tmp = tmp->next->next;
			continue;
		}
		else if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	alloc_args(t_cmd *cmd, int argcount)
{
	cmd->cmd_args = malloc(sizeof(char *) * (argcount + 1));
	if (!cmd->cmd_args)
		return (0);
	cmd->cmd_args[argcount] = NULL;
	return (1);
}

int	parse_cmd_tokens(t_cmd *cmd, t_token **toks)
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
	if (!parse_cmd_tokens(new, toks))
		return (free_cmd(new), NULL);
	return (new);
}

int add_cmds(t_cmd	**head, t_token **toks)
{
	t_cmd *new;
	t_cmd *tmp;

	new = create_cmd(toks);
	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
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

int 	check_pipes(t_token *toks)
{
	if (toks->type == TOKEN_PIPE
		&& (!toks->next
		|| toks->next->type == TOKEN_PIPE))
	{
		ft_dprintf(2,"minihell: syntax error: invalid pipe\n");
		return (2);
	}
	return (0);
}

int 	syntax_checker(t_minishell *main)
{
	t_token *toks;

	toks = main->tokens;
	if (toks->type == TOKEN_PIPE)
		main->last_status = ERR_SYNTAX;
	while (toks)
	{
		main->last_status = check_pipes(toks);
		if (main->last_status)
			return (0);
		toks = toks->next;
	}
	return (1);
}

char	*get_cmd(t_minishell *main, char *line)
{
	main->line = line;
	main->tokens = lexer(line, main);
	print_tokens(main->tokens);
	if (syntax_checker(main))
		return (free_lexer(main->tokens), NULL);
	main->cmd = parse_tokens(main);
	free_lexer(main->tokens);
	if (!main->cmd)
		return (NULL);
	return (line);
}
