/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:37:31 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-26 17:37:31 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

size_t	word_count(const char *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
			if (!s[i])
				break ;
		}
		i++;
	}
	return (words);
}

static const char	*dup_this(char **dst, const char *src, char c)
{
	size_t	len;

	while (*src == c)
		src++;
	len = 0;
	while (src[len] && src[len] != c)
		len++;
	*dst = malloc(sizeof(char) * (len + 1));
	if (*dst == NULL)
		return (NULL);
	ft_memcpy(*dst, src, len);
	(*dst)[len] = '\0';
	src += len + 1;
	return (src);
}

static void	freeall(char **strs, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(strs[i++]);
	free(strs);
	*strs = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	size_t	string_count;
	size_t	i;

	string_count = word_count(s, c);
	strs = malloc(sizeof(char *) * (string_count + 1));
	if (strs)
	{
		strs[string_count] = NULL;
		i = 0;
		while (i < string_count)
		{
			s = dup_this(strs + i++, s, c);
			if (!s)
			{
				freeall(strs, i - 1);
				return (NULL);
			}
		}
	}
	return (strs);
}
