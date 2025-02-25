/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-26 17:12:15 by jbastard          #+#    #+#             */
/*   Updated: 2024-10-26 17:12:15 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	int		s1index;
	int		s2index;
	char	*fstr;

	index = 0;
	s1index = ft_strlen(s1);
	s2index = ft_strlen(s2);
	fstr = malloc (s1index + s2index + 1);
	if (!fstr)
		return (NULL);
	s1index = 0;
	s2index = 0;
	while (s1[s1index])
	{
		fstr[index++] = s1[s1index];
		s1index++;
	}
	while (s2[s2index])
	{
		fstr[index++] = s2[s2index];
		s2index++;
	}
	fstr[index] = '\0';
	return (fstr);
}
