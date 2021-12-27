/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 09:02:55 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/27 15:55:51 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s, int cnts)
{
	while (s[cnts])
		cnts++;
	return (cnts);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	cnts1;
	unsigned int	cnts2;
	unsigned int	i;
	unsigned int	j;
	char			*str;

	cnts1 = 0;
	cnts2 = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	cnts1 = ft_count(s1, cnts1);
	cnts2 = ft_count(s2, cnts2);
	if (!(str = malloc(sizeof(char) * (cnts1 + cnts2 + 1))))
		return (NULL);
	i = -1;
	while (++i < cnts1)
		str[i] = s1[i];
	j = 0;
	while (j < cnts2)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	if (s1)
		free(s1);
	str[i] = '\0';
	return (str);
}
