/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printvoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-11 17:40:48 by jbastard          #+#    #+#             */
/*   Updated: 2024-11-11 17:40:48 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"
#include "../../include/ft_dprintf.h"

static int	hex_len(uintptr_t nb)
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

static char	*ft_itohex(uintptr_t nb)
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
			temp += 87;
		hexret[i] = temp;
		i--;
		nb /= 16;
	}
	return (hexret);
}

int	ft_putlvoid(uintptr_t	n)
{
	char	*s;
	int		len;

	if (!n)
		return (write(STDOUT_FILENO, "(nil)", 5));
	s = ft_itohex(n);
	if (!s)
		return (write(STDOUT_FILENO, "(nil)", 5));
	len = ft_strlen(s);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(s, 1);
	free(s);
	return (len + 2);
}
