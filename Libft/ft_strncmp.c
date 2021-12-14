/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:36:45 by abrun             #+#    #+#             */
/*   Updated: 2021/12/14 17:11:16 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	counter;

	if (n == 0)
		return (0);
	counter = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[counter] == s2[counter] && counter < n
		&& s1[counter] && s2[counter])
		counter++;
	if (counter == n && !s2[counter])
		return (0);
	return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
}
