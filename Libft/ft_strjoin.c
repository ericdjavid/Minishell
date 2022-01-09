/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 09:02:55 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/06 13:22:15 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	unsigned int	cntstot;
	unsigned int	i;
	unsigned int	j;
	char			*str;

	cntstot = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	cntstot = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (cntstot + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	j = 0;
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	j = 0;
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}
