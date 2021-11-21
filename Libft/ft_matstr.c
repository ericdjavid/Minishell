/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:38:51 by abrun             #+#    #+#             */
/*   Updated: 2021/11/21 18:48:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matstr(char **mat, const char *str)
{
	int	c;

	c = 0;
	while (mat[c])
	{
		if (ft_strnstr(mat[c], str, ft_strlen(mat[c])))
			return (c);
		c++;
	}
	return (-1);
}
