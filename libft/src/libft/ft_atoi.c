/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 10:09:42 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-16 10:09:42 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

int	ft_atoi(const char	*nptr)
{
	int	sign;
	int	n;
	int	i;

	sign = 1;
	n = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] <= 13 && nptr[i] >= 9))
		i++;
	if (nptr[i] == '-')
	{
		i++;
		sign *= -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] <= 57 && nptr[i] >= 48)
	{
		n *= 10;
		n += nptr[i] - 48;
		i++;
	}
	return (n * sign);
}
