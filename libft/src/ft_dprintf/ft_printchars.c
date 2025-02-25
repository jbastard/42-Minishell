/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:11 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 12:06:56 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-10 13:42:03 by jbastard          #+#    #+#             */
/*   Updated: 2024-11-10 13:42:03 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"
#include "../../include/ft_dprintf.h"

int	ft_putchar(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putlstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ((write(fd, "(null)", 6)));
	while (s[i])
		ft_putchar(s[i++], fd);
	return (ft_strlen(s));
}
