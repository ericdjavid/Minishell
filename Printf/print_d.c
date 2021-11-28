/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:08:22 by abrun             #+#    #+#             */
/*   Updated: 2021/11/28 16:44:08 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_d(int arg, int fd)
{
	char	*itoa;
	size_t	len;

	itoa = ft_itoa(arg);
	if (!itoa)
		return (-1);
	len = ft_strlen(itoa);
	write(fd, itoa, len);
	free(itoa);
	return (len);
}
