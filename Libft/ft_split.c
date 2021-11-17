/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:07:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 13:49:57 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_n_cases(char *str, char c)
{
	int	n;

	n = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		n++;
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
	}
	return (n);
}

int	get_len_str(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*fill_split(char *str, char c)
{
	int		len_str;
	char	*split;
	int		count;

	len_str = get_len_str(str, c);
	split = malloc(len_str + 1);
	if (!split)
		return (0);
	count = 0;
	while (str[count] && str[count] != c)
	{
		split[count] = str[count];
		count++;
	}
	split[count] = 0;
	return (split);
}

char	*get_next_str(char *str, char c, int count)
{
	if (!count)
	{
		while (*str && *str == c)
			str++;
	}
	else
	{
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
	}
	return (str);
}

char	**ft_split(char *str, char c)
{
	int		n_cases;
	char	**split;
	int		count;

	n_cases = get_n_cases(str, c);
	split = malloc(sizeof(char *) * (n_cases + 1));
	if (!split)
		return (0);
	count = 0;
	while (*str && count < n_cases)
	{
		str = get_next_str(str, c, count);
		split[count] = fill_split(str, c);
		if (!*split)
		{
			free_matc(split);
			return (0);
		}
		count++;
	}
	split[count] = 0;
	return (split);
}
