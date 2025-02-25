/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 15:22:33 by jbastard          #+#    #+#             */
/*   Updated: 2024-11-11 15:22:33 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

void	ft_putunbr(unsigned int n, int fd)
{
	if (n / 10)
		ft_putunbr(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
}
