/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:11 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 13:01:10 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"

int	ft_dprintf(int fd, const char *format, ...);
int	ft_putchar(int c, int fd);
int	ft_putlstr(char	*string, int fd);
int	ft_putlvoid(uintptr_t n);
int	ft_putlnbr(int n, int fd);
int	ft_putlunbr(unsigned int n, int fd);
int	ft_need_hex(unsigned int deci, int param, int fd);

#endif
