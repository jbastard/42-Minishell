/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 07:52:57 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/24 15:30:17 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	exit_error(char *source, int isper, int exitcode)
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
