/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:17:09 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 11:53:33 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t			s1_len;
	unsigned char	*dst;

	s1_len = ft_strlen(s1);
	dst = malloc(sizeof(char) * (s1_len + 1));
	if (!dst)
		return (NULL);
	while (s1_len--)
		*dst++ = *s1++;
	*dst = 0;
	return ((char *)dst - s1_len);
}
