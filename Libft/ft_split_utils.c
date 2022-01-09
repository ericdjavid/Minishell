/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:30:04 by abrun             #+#    #+#             */
/*   Updated: 2022/01/05 17:30:41 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	browse_classic(char *str, char *charset, char *specs)
{
	int		n;
	char	c;

	n = 0;
	while (str[n] && !ft_strchr(specs, str[n])
		&& !ft_strchr(charset, str[n]))
	{
		if (str[n] == '"' || str[n] == 39)
		{
			c = str[n];
			n++;
			while (str[n] && str[n] != c)
				n++;
			n++;
			if (!str[n])
				return (n);
			browse_classic(str + n, charset, specs);
		}
		else
			n++;
	}
	return (n);
}

int	browse_str(char *str, char *charset)
{
	char	specs[4];
	char	c;
	int		n;

	specs[0] = '|';
	specs[1] = '>';
	specs[2] = '<';
	specs[3] = 0;
	n = 0;
	if (!ft_strchr(specs, *str) && !ft_strchr(charset, *str))
		return (browse_classic(str, charset, specs));
	else if (ft_strchr(specs, *str))
	{
		c = *str;
		while (str[n] && str[n] == c)
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
	int		c[2];
	char	k;

	len_str = browse_str(str, charset);
	split = malloc(len_str + 1);
	if (!split)
		return (0);
	c[0] = 0;
	c[1] = 0;
	while (c[0] < len_str)
	{
		if (str[c[0]] == 39 || str[c[0]] == '"')
		{
			k = str[c[0]];
			while (++c[0] < len_str && str[c[0]] != k)
				split[c[1]++] = str[c[0]];
		}
		else
			split[c[1]++] = str[c[0]];
		c[0]++;
	}
	split[c[1]] = 0;
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
