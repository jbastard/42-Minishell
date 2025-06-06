/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_kind_of_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:36:19 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/20 14:28:16 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir(t_redir *redir)
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

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd_args)
			free_tab(cmd->cmd_args);
		free(cmd->path);
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

void	free_local_env(t_env **env)
{
	t_env	*temp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = temp;
	}
	*env = NULL;
}
