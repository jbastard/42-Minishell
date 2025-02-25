/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:09:02 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-26 17:09:02 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

static size_t	isinset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	check_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (isinset(s1[i], set))
		i++;
	return (i);
}

static size_t	check_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (isinset(s1[i], set))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = check_start(s1, set);
	end = check_end(s1, set);
	if ((end - start) <= 0)
	{
		trim_str = malloc(1);
		if (!trim_str)
			return (NULL);
		trim_str[0] = '\0';
		return (trim_str);
	}
	trim_str = malloc (sizeof(*s1) * (end - start + 1));
	if (!trim_str)
		return (NULL);
	while (start < end)
		trim_str[i++] = s1[start++];
	trim_str[i] = '\0';
	return (trim_str);
}
