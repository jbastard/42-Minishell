/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:02:57 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-26 17:02:57 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

static char	*ft_strcpy(const char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str_dest;
	size_t	len;

	len = ft_strlen(s) + 1;
	str_dest = malloc (len);
	if (!str_dest)
		return (0);
	ft_strcpy(s, str_dest);
	return (str_dest);
}
