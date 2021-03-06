/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:20:54 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 16:57:18 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_s(char *arg, int fd)
{
	int	len;

	if (!arg)
		return (0);
	len = ft_strlen(arg);
	write(fd, arg, len);
	return (len);
}
