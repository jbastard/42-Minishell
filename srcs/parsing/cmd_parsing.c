/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:24:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/13 10:15:23 by jbastard         ###   ########.fr       */
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
//
//char 	**fill_args(t_token **toks)
//{
//	char	**args;
//	t_token *curr;
//	int 	argcount;
//	int		i;
//
//	i = 0;
//	argcount = args_count(*toks);
//	if (argcount == 0)
//		return (NULL);
//	args = malloc(sizeof(char *) * (argcount + 1));
//	curr = *toks;
//	while (curr && curr->type != TOKEN_PIPE && i < argcount)
//	{
//		if (is_redir(curr))
//		{
//			curr = curr->next->next;
//			continue ;
//		}
//		if (curr->type == TOKEN_WORD)
//			args[i++] = ft_strdup(curr->value);
//		curr = curr->next;
//	}
//	args[i] = NULL;
//	*toks = curr;
//	return (args);
//}
//
//t_cmd 	*create_cmd(t_token **toks)
//{
//	t_cmd	*new;
//
//	new = malloc(sizeof(t_cmd));
//	init_cmd(new);
//	new->cmd_args = fill_args(toks);
//	if (new->cmd_args == NULL)
//		return (free_cmd(new),NULL);
//	printf("token type %d\ntoken value %s\n", (*toks)->type, (*toks)->value);
//	while (*toks && (*toks)->type != TOKEN_PIPE)
//	{
//		if (is_redir(*toks))
//		{
//			printf("OK\n");
//			if (!(*toks)->next || (*toks)->next->type != TOKEN_WORD)
//				return (free_cmd(new),NULL);
//			add_redir(&(new->redir), (*toks)->type, (*toks)->next->value);
//			(*toks) = (*toks)->next->next;
//		}
//		else
//			(*toks) = (*toks)->next;
//	}
//	return (new);
//}

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

void 	care_about_pipes(t_minishell *main ,t_cmd *cmds, t_token *toks)
{
	t_token *tmp;

	tmp = toks;
	if (tmp->type == TOKEN_PIPE && cmds == NULL)
		handle_error(main, ERR_SYNTAX, "|");
	if (tmp->type == TOKEN_PIPE)
		if (!tmp->next || tmp->next->type == TOKEN_PIPE)
			handle_error(main, ERR_SYNTAX, "|");
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == TOKEN_PIPE)
		handle_error(main, ERR_SYNTAX, "newline");
}

t_cmd	*parse_tokens(t_minishell *main)
{
	t_cmd	*cmds;
	t_token	*toks;

	cmds = NULL;
	toks = main->tokens;
	while (toks)
	{
//		care_about_pipes(main, cmds, toks);
		if (!add_cmds(&cmds, &toks))
			return (NULL);
		if (toks && toks->type == TOKEN_PIPE)
			toks = toks->next;
	}
	return (cmds);
}

//int 	syntax_checker(t_token *toks)
//{
//	return (1);
//}

char	*get_cmd(t_minishell *main, char *line)
{
	main->line = line;
	main->tokens = lexer(line);
	print_tokens(main->tokens);
//	if (!syntax_checker(main->tokens))
//		return (free_lexer(main->tokens), NULL);
	main->cmd = parse_tokens(main);
	free_lexer(main->tokens);
	if (!main->cmd)
		return (NULL);
	return (line);
}
