/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:40:53 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/10 12:14:23 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_simple_quotes(char *str)
{
	int		i;
	int		j;
	char	*str2;

	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!str2)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		str2[j] = str[i];
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

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
		if (!ft_isalnum(str[i]) && str[i] != '_')
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

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=' && i++)
			break ;
	}
	k = i;
	j = -1;
	while (str[i] && ++j >= 0)
		i++;
	tmp = malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (str[k] != '\0')
		tmp[++i] = str[k++];
	tmp[i] = '\0';
	return (tmp);
}
