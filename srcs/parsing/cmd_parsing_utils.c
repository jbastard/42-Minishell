/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:29:28 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/17 08:07:54 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_cmds(t_cmd	**head, t_token **toks)
{
	t_cmd	*new;
	t_cmd	*tmp;

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

int	args_count(t_token *toks)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = toks;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
				return (0);
			tmp = tmp->next->next;
			continue ;
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

void	init_cmd(t_cmd *new)
{
	new->redir = NULL;
	new->next = NULL;
	new->cmd_args = NULL;
	new->path = NULL;
}

int	is_redir(t_token *toks)
{
	if (toks->type != TOKEN_PIPE && toks->type != TOKEN_WORD)
		return (1);
	return (0);
}
