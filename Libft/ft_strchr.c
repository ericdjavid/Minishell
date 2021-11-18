/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:16:02 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 09:20:42 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	unsigned int	counter;

	counter = 0;
	while (s[counter])
	{
		if (s[counter] == c)
			return (1);
		counter++;
	}
	if (c == '\0' && s[counter] == '\0')
		return (1);
	return (0);
}
