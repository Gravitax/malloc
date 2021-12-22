/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marcaboye@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:07:59 by maboye            #+#    #+#             */
/*   Updated: 2021/12/22 09:55:35 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

void			ft_printf(int fd, const char *str, ...)
{
	va_list	args;

	if (!str)
		return ;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			++str;
			if (*str == 's')
				ft_putstr_fd(va_arg(args, char *), fd);
			else if (*str == 'd' || *str == 'c')
				ft_putnbr_fd(va_arg(args, int), fd);
			++str;
		}
		else
			ft_putchar_fd(*str++, fd);
	}
	va_end(args);
}
