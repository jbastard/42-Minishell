/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:47:33 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/18 12:55:13 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_minishell *main)
{
	free(main->prompt);
	free_cmd(main->cmd);
	free(main->builtins);
	free_tab(main->env);
	free_local_env(&main->local_vars);
}
