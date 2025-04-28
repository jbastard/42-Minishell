/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:58:17 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/20 12:41:11 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_paths(char **envp)
{
	char	**full_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':');
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**full_path;
	char	*temp;
	char	*final_path;
	int		i;

	i = 0;
	full_path = get_paths(envp);
	if (!full_path)
		return (NULL);
	while (full_path[i])
	{
		temp = ft_strjoin(full_path[i], "/");
		final_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(final_path, F_OK) == 0)
			return (free_tab(full_path), final_path);
		free(final_path);
		i++;
	}
	free_tab(full_path);
	return (NULL);
}

int	check_cmd(t_minishell *main)
{
	t_cmd	*temp;

	temp = main->cmd;
	while (temp)
	{
		if (temp->cmd_args && !access(temp->cmd_args[0], X_OK | F_OK))
		{
			temp->path = ft_strdup(temp->cmd_args[0]);
			temp = temp->next;
			continue ;
		}
		else if (temp->cmd_args && temp->cmd_args[0][0] == '/')
			return (handle_error(main, ERR_FILE_NOT_FOUND,
					temp->cmd_args[0]));
		if (temp->cmd_args)
			temp->path = find_cmd_path(temp->cmd_args[0], main->env);
		temp = temp->next;
	}
	return (0);
}
