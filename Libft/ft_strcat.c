/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:21:18 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 13:45:52 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dst, const char *src)
{
	size_t			dstlen;
	unsigned int	counter;

	counter = 0;
	dstlen = 0;
	while (dst[dstlen])
		dstlen++;
	while (src[counter])
	{
		dst[dstlen + counter] = src[counter];
		counter++;
	}
	dst[dstlen + counter] = '\0';
}
