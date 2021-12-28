/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:46:28 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 16:36:56 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_arg(char c, va_list lst, int fd)
{
	if (c == 'd')
		return (print_d(va_arg(lst, int), fd));
	else if (c == 's')
		return (print_s(va_arg(lst, char *), fd));
	else if (c == 'x')
		return (print_x(va_arg(lst, unsigned int), fd));
	return (-1);
}	

int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	lst;

	va_start(lst, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			print_arg(*s, lst, fd);
		}
		else
			write(fd, s, 1);
		if (*s)
			s++;
	}
	return (1);
}
