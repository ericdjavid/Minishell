/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:07:16 by abrun             #+#    #+#             */
/*   Updated: 2022/01/02 18:46:07 by edjavid          ###   ########.fr       */
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
		else if (str[n] == '\'')
		{
			n++;
			while (str[n] && str[n] != '\'')
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

int		ft_only_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

char	*fill_split(char *str, char *charset)
{
	int		len_str;
	char	*split;
	int		count;
	int		c_2;
	char	*neo_split;

	len_str = browse_str(str, charset);
	split = malloc(len_str + 1);
	if (!split)
		return (0);
	count = 0;
	c_2 = 0;
	while (count < len_str)
	{
		split[c_2++] = str[count];
		count++;
	}
	split[c_2] = 0;
	if (len_str == 2 && (is_surrounded(split, len_str - 1, '"') == TRUE
		|| is_surrounded(split, len_str - 1, '\'') == TRUE))
	{
		free(split);
		split = malloc(2);
		// TODO: pbm avec espace, il faudrait mettre une valeur nulle
		split[0] = ' ';
		split[1] = 0;
		return (split);
	}
	if (ft_only_quotes(split, '\'') || ft_only_quotes(split, '"'))
	{
		free(split);
		split = malloc(2);
		split[0] = ' ';
		split[1] = 0;
		return (split);
	}
	if (is_surrounded(split, len_str - 1, '"') == TRUE)
	{
		neo_split = ft_remove_quotes(split);
		free(split);
		return (neo_split);
	}
	if (is_surrounded(split, len_str - 1, '\'') == TRUE)
	{
		neo_split = ft_remove_simple_quotes(split);
		free(split);
		return (neo_split);
	}
	return (split);
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

	if (!str)
		return (NULL);
	n_cases = get_n_cases(str, charset);
	split = malloc(sizeof(char *) * (n_cases + 1));
	if (!split)
		return (0);
	count = 0;
	while (*str && count < n_cases)
	{
		str = get_next_str(str, charset, count);
		split[count] = fill_split(str, charset);
		if (!split[count])
		{
			free_matc(split);
			return (0);
		}
		count++;
	}
	split[count] = 0;
	return (split);
}
