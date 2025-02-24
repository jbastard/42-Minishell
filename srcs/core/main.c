/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/24 15:24:43 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		main(int ac, char **av, char **envp)
{
	char	*input;

	(void)av;
	(void)ac;
	(void)envp;
	sig_handler();
	while (1)
	{
		input = get_cmd(envp);
		if (!input)
			exit_error("", 0, 0);
		free(input);
	}
}
