/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_kind_of_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:36:19 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/20 12:40:58 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		free(redir->file);
		redir = redir->next;
		free(tmp);
	}
	redir = NULL;
}

void 	free_cmd(t_cmd *cmd)
{
	t_cmd 	*tmp;

	while (cmd)
	{
		if (cmd->cmd_args) {
			free_tab(cmd->cmd_args);
		}
		free_redir(cmd->redir);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	cmd = NULL;
}

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	if (!tabl)
		return ;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
	tabl = NULL;
}

void	free_lexer(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->value)
			free(token->value);
		temp = token;
		token = token->next;
		free(temp);
	}
	token = NULL;
}
