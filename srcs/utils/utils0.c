/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:35:38 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/14 16:15:59 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_whitespaces(char c)
{
	return (c <= 32);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	count_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		i++;
		count++;
	}
	return (count);
}
