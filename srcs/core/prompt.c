/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:20:03 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/10 17:30:02 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (main->prompt)
			free(main->prompt);
		main->prompt = temp2;
	}
	else
		main->prompt = ft_strjoin(buffer, "> ");
	free_tab(temp);
}
