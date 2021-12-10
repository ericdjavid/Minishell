/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:07:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/10 22:38:37 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

#include <stdio.h>

int	browse_str(char *str, char c)
{
	int	n;

	n = 0;
	while (str[n] && str[n] != c)
	{
		if (str[n] == '"')
		{
			n++;
			while (str[n] && str[n] != '"')
				n++;
			n++;
			if (!str[n])
				return (n);
			browse_str(str + n, c);
		}
		else
			n++;
	}
	return (n);
}

int	get_n_cases(char *str, char c)
{
	int	n;

	n = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		n++;
		str += browse_str(str, c);
		while (*str && *str == c)
			str++;
	}
	return (n);
}

char	*fill_split(char *str, char c)
{
	int		len_str;
	char	*split;
	int		count;
	char	*splitted2;

	len_str = browse_str(str, c);
	split = malloc(len_str + 1);
	if (!split)
		return (0);
	count = 0;
	while (count < len_str)
	{
		split[count] = str[count];
		count++;
	}
	split[count] = 0;
	splitted2 = ft_remove_quotes(split);
	free(split);
	return (splitted2);
}

char	*get_next_str(char *str, char c, int count)
{
	if (!count)
		while (*str && *str == c)
			str++;
	else
	{
		str += browse_str(str, c);
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
