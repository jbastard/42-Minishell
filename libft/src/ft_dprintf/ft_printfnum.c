/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:11 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 12:44:27 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 14:58:31 by jbastard          #+#    #+#             */
/*   Updated: 2024-11-11 14:58:31 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"
#include "../../include/ft_dprintf.h"

int	ft_putlnbr(int n, int fd)
{
	int	i;

	i = 1;
	if (!n)
		return ((write(fd, "0", 1)));
	if (n < 0)
	{
		write (fd, "-", 1);
		i++;
		n *= -1;
	}
	ft_putunbr(n, fd);
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putlunbr(unsigned int n, int fd)
{
	int	i;

	i = 1;
	if (!n)
		return ((write(fd, "0", 1)));
	ft_putunbr(n, fd);
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}
