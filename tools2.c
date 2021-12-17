/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:40:53 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/17 18:43:02 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_position(char c, char c2, char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c2)
	{
		if (str[i] == c)
			return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

t_bool	is_quest(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (FALSE);
		if (!ft_isalnum(str[i]))
			return (TRUE);
	}
	return (FALSE);
}

char	*add_value_name(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	k = i;
	j = 0;
	while (str[i])
	{
		j++;
		i++;
	}
	tmp = malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[k] != '\0')
	{
		tmp[i] = str[k];
		k++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = dst;
	n = size;
	s = src;
	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}

char *ft_deal_space(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	split = ft_split(str, " ");
	while (split[i])
	{
		// printf("splitted val %d is |%s|\n", i, split[i]);
		i++;
	}
	free_matc(split);
	return (str);
}

char	*ft_get_dollar_var(char *str, t_control *list)
{
	t_element	*tmp;
	char		*tmp_char;
	char		*deal_space;
	// int			after;

	tmp_char = NULL;
	deal_space = NULL;

	if (ft_strchr(str, ' ') )
	{
		deal_space = ft_deal_space(str);
	}
	(void)deal_space;

	tmp = ft_is_in_list(list, str);
	if (!tmp)
		return (NULL);
	// printf("(ft_get_doll)tmp->str is |%s|\n", tmp->str);
	free(tmp_char);
	tmp_char = NULL;
	tmp_char = add_value_name(tmp->str);
	// printf("(ft_get_doll)new value name is |%s|\n", tmp_char);
	return (tmp_char);
}

int	ft_is_space_before_qual(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
