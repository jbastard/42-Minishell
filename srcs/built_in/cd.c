/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:37:51 by nlecreux          #+#    #+#             */
/*   Updated: 2025/04/28 07:49:00 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	get_cd_path(t_minishell *main, char *path)
{
	char	buffer[1024];
	char	*tmp;
	char	*cwd;

	(void)main;
	cwd = getcwd(buffer, 1024);
	if (!cwd)
		return (perror("cd"), 1);
	tmp = ft_strjoin(cwd, "/");
	path = ft_strjoin_free(tmp, path);
	if (chdir(path) != 0)
		return (perror("cd"), free(path), 1);
	free(path);
	return (0);
}

int	cd_command(char **args, t_minishell *main)
{
	char	*path;

	(void)main;
	if (!args || !args[0] || args[0][0] == 0)
	{
		path = getenv("HOME");
		if (!chdir(path))
			return (0);
		else
			return (printf("minishell: cd: HOME not set\n"), 1);
	}
	else
		path = args[0];
	if (path[0] == '/')
	{
		if (chdir(path) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (get_cd_path(main, path));
}
