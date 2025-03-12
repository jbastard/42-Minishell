/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:24:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/12 11:48:52 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	init_cmd(t_cmd *new)
{
	new->cmd_args = NULL;
	new->path = NULL;
	new->redir = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	new->next = NULL;
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
	new->type = type;
	new->file = strdup(file);
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

char 	**fill_args(t_token **toks)
{
	char	**args;
	t_token *curr;
	int 	argcount;
	int		i;

	i = 0;
	argcount = args_count(*toks);
	if (!argcount)
		return (NULL);
	args = malloc(sizeof(char *) * (argcount + 1));
	args[argcount] = NULL;
	curr = *toks;
	while (curr && i < argcount)
	{
		if (curr->next && curr->next->type == TOKEN_WORD && is_redir(curr))
		{
			curr = curr->next->next;
			if (!curr)
				break;
		}
		if (curr->type == TOKEN_WORD)
			args[i] = ft_strdup(curr->value);
		curr = curr->next;
		i++;
	}
	return (args);
}

t_cmd 	*create_cmd(t_token **toks)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	init_cmd(new);
	new->cmd_args = fill_args(toks);
	if (new->cmd_args == NULL)
		return (NULL);
	while (*toks && (*toks)->type != TOKEN_PIPE)
	{
		if (is_redir(*toks))
		{
			if (!(*toks)->next || (*toks)->next->type != TOKEN_WORD)
				return (printf("Syntax error near redirection\n"), NULL);
			add_redir(&(new->redir), (*toks)->type, (*toks)->next->value);
			(*toks) = (*toks)->next->next;
		}
		else
			(*toks) = (*toks)->next;
	}
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

void 	free_parser(t_minishell *main)
{
	t_cmd 	*ctmp;
	t_redir	*rtmp;

	while (main->cmd)
	{
		free_tab(main->cmd->cmd_args);
		while (main->cmd->redir)
		{
			rtmp = main->cmd->redir;
			free(main->cmd->redir->file);
			main->cmd->redir = main->cmd->redir->next;
			free(rtmp);
		}
		ctmp = main->cmd;
		main->cmd = main->cmd->next;
		free(ctmp);
	}
}

char	*get_cmd(t_minishell *main, char *line)
{
	main->line = line;
	main->tokens = lexer(main->line);
	main->cmd = parse_tokens(main);
	if (!main->cmd)
		return (NULL);
	free_lexer(main->tokens);
	main->tokens = NULL;
	return (line);
}
