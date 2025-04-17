/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ws_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:09:22 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 13:58:10 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ws_word_count(const char *s)
{
	size_t	words;
	size_t	i;
	int		quotes;

	quotes = 0;
	words = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] > 32)
		{
			words++;
			while (s[i] > 32 && s[i])
				i++;
			if (!s[i])
				break ;
		}
		i++;
	}
	return (words);
}

static const char	*dup_this(char **dst, const char *src)
{
	size_t	len;

	while (*src <= 32)
		src++;
	len = 0;
	while (src[len] && src[len] > 32)
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
}

char	**ft_ws_split(const char *s)
{
	char	**strs;
	size_t	string_count;
	size_t	i;

	string_count = ws_word_count(s);
	strs = malloc(sizeof(char *) * (string_count + 1));
	if (strs)
	{
		strs[string_count] = NULL;
		i = 0;
		while (i < string_count)
		{
			s = dup_this(strs + i++, s);
			if (!s)
			{
				freeall(strs, i - 1);
				return (NULL);
			}
		}
	}
	return (strs);
}
