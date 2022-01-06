/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:45:23 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/06 16:58:02 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_var_name(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_count(char *str, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			nb++;
	}
	return (nb);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*str2;
	int		nb;

	if (!str)
		return (NULL);
	nb = ft_count(str, '\"');
	str2 = malloc(sizeof(char) * (ft_strlen(str) - nb + 1));
	if (!str2)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			continue ;
		str2[j] = str[i];
		j++;
	}
	str2[j] = '\0';
	return (str2);
}
