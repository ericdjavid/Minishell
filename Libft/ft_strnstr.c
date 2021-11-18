/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:37:51 by abrun             #+#    #+#             */
/*   Updated: 2020/11/23 09:20:37 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	c;
	unsigned int	c_n;

	c = 0;
	c_n = 0;
	if (len <= 0 && !*needle)
		return ((char *)haystack);
	while (haystack[c] && c < len)
	{
		while ((haystack[c + c_n] == needle[c_n])
			&& haystack[c + c_n] && c + c_n < len)
			c_n++;
		if (!needle[c_n])
			return ((char *)&haystack[c]);
		c_n = 0;
		c++;
	}
	return (NULL);
}
