/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 07:52:57 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/10 17:15:57 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_error(char *source, int isper, int exitcode)
{
	if (exitcode >= 0)
		printf("exit\n");
	if (isper)
		perror(source);
	else if (source)
		printf("%s", source);
	if (exitcode >= 0)
		exit(exitcode);
}
