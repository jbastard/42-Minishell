/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:52:35 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/26 09:22:33 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 16:08:18 by jbastard          #+#    #+#             */
/*   Updated: 2024-11-11 16:08:18 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"
#include "../../include/ft_dprintf.h"

static int	hex_len(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb / 16)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

static char	*ft_itohex(unsigned int nb, int param)
{
	int		temp;
	int		i;
	char	*hexret;

	i = hex_len(nb);
	hexret = malloc((i + 1) * sizeof(char *));
	if (!hexret)
		return (NULL);
	hexret [i + 1] = '\0';
	while (nb)
	{
		temp = nb % 16;
		if (temp < 10)
			temp += 48;
		else
			temp += 55;
		if (param == 'x')
			hexret[i] = ft_tolower(temp);
		else
			hexret[i] = temp;
		i--;
		nb /= 16;
	}
	return (hexret);
}

int	ft_need_hex(unsigned int deci, int param, int fd)
{
	char	*s;
	int		len;

	if (deci == 0)
		return ((write(fd, "0", 1)));
	s = ft_itohex(deci, param);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
