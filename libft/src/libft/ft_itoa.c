/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 16:47:51 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-31 16:47:51 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

static size_t	intlen(int n)
{
	size_t	c;

	c = 0;
	if (n <= 0)
	{
		c++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static void	filln(int n, size_t len, char *new)
{
	new[0] = '-';
	if (n == -2147483648)
	{
		new[len - 1] = '8';
		n /= 10;
		len--;
	}
	n = -n;
	while (len > 1)
	{
		new[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*new;

	len = intlen(n);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len] = 0;
	if (n >= 0)
	{
		while (len > 0)
		{
			new[len - 1] = (n % 10) + 48;
			n /= 10;
			len--;
		}
	}
	else
		filln(n, len, new);
	return (new);
}
