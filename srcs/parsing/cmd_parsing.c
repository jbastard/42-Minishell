/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:34:15 by jbastard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/04 10:57:06 by jbastard         ###   ########.fr       */
=======
/*   Updated: 2025/03/04 15:07:23 by nlecreux         ###   ########.fr       */
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

<<<<<<< HEAD
void	update_prompt(t_minishell *mnsl)
{
	char	buffer[PATH_MAX];
	if (mnsl->prompt)
		free(mnsl->prompt);
	getcwd(buffer, PATH_MAX);
	mnsl->prompt = ft_strjoin(buffer, ">");
=======
int	count_chars_tab(char **tabl)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tabl[i])
	{
		count += ft_strlen(tabl[i]);
		i++;
	}
	return (count);
}

char	*better_join(char **tabl, char sep)
{
	int		i1;
	int		i2;
	int		i3;
	char	*new;

	i1 = 0;
	i3 = 0;
	new = malloc(count_chars_tab(tabl) + count_args(tabl));
	while (tabl[i1])
	{
		i2 = 0;
		while (tabl[i1][i2])
			new[i3++] = tabl[i1][i2++];
		if (tabl[i1 + 1])
			new[i3++] = sep;
		i1++;
	}
	new[i3] = 0;
	return (new);
}

void	update_prompt(t_minishell *main)
{
	char	buffer[PATH_MAX];
	char	**temp;
	char	*temp2;
	int		count;
	
	if (main->prompt)
		free(main->prompt);
	getcwd(buffer, PATH_MAX);
	temp = ft_split(buffer, '/');
	count = count_args(temp);
	if (count > 2)
	{
		main->prompt = better_join(&temp[count - 2], '/');
		temp2 = ft_strjoin(main->prompt, "> ");
		free(main->prompt);
		main->prompt = temp2;
	}
	else
		main->prompt = ft_strjoin(buffer, "> ");
	free_tab(temp);
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
}

char	*get_cmd(t_minishell *mnsl)
{
	char	*line;
	
<<<<<<< HEAD
	update_prompt(mnsl);
	line = readline(mnsl->prompt);
=======
	update_prompt(main);
	line = readline(main->prompt);
>>>>>>> ccd702188509158dda85c6eb911d41d2cfb05e18
	return (line);
}

