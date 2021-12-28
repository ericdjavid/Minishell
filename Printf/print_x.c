/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:55:55 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 15:56:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_x(unsigned int arg, int fd)
{
	int		len;
	char	*hexa;

	hexa = convert_hexa(arg);
	if (!hexa)
		return (-1);
	len = ft_strlen(hexa);
	write(fd, hexa, len);
	return (len);
}
