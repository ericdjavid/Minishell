/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:18:58 by abrun             #+#    #+#             */
/*   Updated: 2022/01/11 16:52:04 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin_free_n(char *s1, const char *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*strjoin;
	size_t			strjoin_len;
	unsigned int	counter;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoin_len = s1_len + s2_len + 2;
	strjoin = malloc(sizeof(char) * strjoin_len);
	if (!strjoin)
		return (NULL);
	counter = -1;
	while (++counter < s1_len)
		strjoin[counter] = s1[counter];
	if (s1)
		free(s1);
	while (counter - s1_len < s2_len)
	{
		strjoin[counter] = s2[counter - s1_len];
		counter++;
	}
	strjoin[counter] = '\n';
	strjoin[counter + 1] = 0;
	return (strjoin);
}
