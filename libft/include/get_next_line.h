/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:00:42 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/05 14:39:56 by nlecreux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

// char		*ft_strjoingnl(const char *s1, const char *s2);
// int			ft_strlengnl(const char *s);
// char		*ft_strdupgnl(const char *s);
// char		*ft_strchrgnl(const char *s, int c);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_linel(int fd, char *buf, char *backup);
char		*get_backup(char *line);
char		*get_next_line(int fd);

#endif