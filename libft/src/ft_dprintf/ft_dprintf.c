/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:00:11 by jbastard          #+#    #+#             */
/*   Updated: 2025/02/25 13:03:59 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/ft_dprintf.h"

static int	printif(int fd, const char param, va_list	args)
{
	if (param == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	if (param == 's')
		return (ft_putlstr(va_arg(args, char *), fd));
	if (param == 'p')
		return (ft_putlvoid(va_arg(args, uintptr_t)));
	if (param == 'd' || param == 'i')
		return (ft_putlnbr(va_arg(args, int), fd));
	if (param == 'u')
		return (ft_putlunbr(va_arg(args, unsigned int), fd));
	if (param == 'x' || param == 'X')
		return (ft_need_hex(va_arg(args, unsigned int), param, fd));
	if (param == '%')
		return (ft_putchar('%', fd));
	return (0);
}

int	ft_dprintf(int fd, const char *param, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, param);
	i = 0;
	len = 0;
	while (param[i])
	{
		if (param[i] == '%')
		{
			len += printif(fd, param[i + 1], args);
			i += 2;
		}
		else
			len += ft_putchar(param[i++], fd);
	}
	va_end(args);
	return (len);
}
