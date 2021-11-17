/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:36:45 by abrun             #+#    #+#             */
/*   Updated: 2020/11/19 14:17:44 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	counter;

	if (n == 0)
		return (0);
	counter = 0;
	while (s1[counter] == s2[counter] && counter < n
		&& s1[counter] && s2[counter])
		counter++;
	if (counter == n)
		return (0);
	return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
}
