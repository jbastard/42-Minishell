/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:31:05 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/28 17:17:10 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cmd_join(char **cmd, int old, int i)
{
	char	*f_arg;

	f_arg = ft_strdup(cmd[old]);
	while (old + 1 <= i)
	{
		f_arg = ft_strjoin(cmd[old], " ");
		f_arg = ft_strjoin(f_arg, cmd[old + 1]);
		old++;
	}
	printf("%s", f_arg);
}

int d_quotes(char **cmdtab, int i) //rajouter struct minishell donc struct cmd
{
	int j;
	int old;

	old = i;
	while (cmdtab[i])
	{
		j = 0;
		while (cmdtab[i][j])
		{
			if (cmdtab[i][j] == DQUOTES)
			{
				cmd_join(cmdtab, old, i);
			}
			j++;
		}
		i++;
	}
	return(i + 1);
}
//int s_quotes(char **cmd)

void cmd_filer(char *line)
{
	int i;
	int j;
	char **cmdtab;

	i = 0;
	cmdtab = ft_split(line, ' ');
	while (cmdtab[i])
	{
		j = 0;
		while (cmdtab[i][j])
		{
			if (cmdtab[i][j] == DQUOTES)
				i = d_quotes(cmdtab, i);
			else if (cmdtab[i][j] == SQUOTES)
				exit(0);
//				i += s_quotes(cmdtab, i);
			j++;
		}
//		printf("%s", cmdtab[i]);
		i++;
	}
//	free_tab(cmdtab);
}

int main()
{
	char *line = "Test de \"la fonction\" split";
//	printf("%s\n", line);
	cmd_filer(line);
	printf("\n");
}