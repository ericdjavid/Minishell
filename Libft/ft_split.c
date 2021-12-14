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

int	browse_str(char *str, char *charset)
{
	int	n;

	n = 0;
	while (str[n] && !ft_strchr(charset, str[n]))
	{
		if (str[n] == '"')
		{
			n++;
			while (str[n] && str[n] != '"')
				n++;
			n++;
			if (!str[n])
				return (n);
			browse_str(str + n, charset);
		}
		else
			n++;
	}
	return (n);
}

int	get_n_cases(char *str, char *charset)
{
	int	n;

	n = 0;
	while (*str && ft_strchr(charset, *str))
		str++;
	while (*str)
	{
		n++;
		str += browse_str(str, charset);
		while (*str && ft_strchr(charset, *str))
			str++;
	}
	return (n);
}

char	*fill_split(char *str, char *charset)
{
	int		len_str;
	char	*split;
	int		count;
	char	*splitted2;

	len_str = browse_str(str, charset);
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

char	*get_next_str(char *str, char *charset, int count)
{
	if (!count)
		while (*str && ft_strchr(charset, *str))
			str++;
	else
	{
		str += browse_str(str, charset);
		while (*str && ft_strchr(charset, *str))
			str++;
	}
	return (str);
}

char	**ft_split(char *str, char *charset)
{
	int		n_cases;
	char	**split;
	int		count;

	n_cases = get_n_cases(str, charset);
	split = malloc(sizeof(char *) * (n_cases + 1));
	if (!split)
		return (0);
	count = 0;
	while (*str && count < n_cases)
	{
		str = get_next_str(str, charset, count);
		split[count] = fill_split(str, charset);
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
