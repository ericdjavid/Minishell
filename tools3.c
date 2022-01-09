/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:25:15 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/06 16:48:31 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_unpair_char_before(char *str, int i, char c)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (i == 0)
		return (1);
	while (str[j] && j < i)
	{
		if (str[j] == c)
			count++;
		j++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

char	*ft_strcut(char *str, int size, int pos)
{
	int		i;
	int		j;
	char	*new;

	if (ft_strlen(str) - size == 0)
	{
		free(str);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && i < pos)
		new[j++] = str[i++];
	i += size;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

int	check_unpair_chars(char *str, int i)
{
	if (str[i] && str[i] == '\'' && no_unpair_char_before(str, i, '"'))
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] != '\'')
			return (-1);
	}
	return (i);
}

char	*ft_change_str_value(char *str_good, char *str, int size, int i)
{
	if (str_good == NULL)
		str = ft_strcut(str, size, i);
	else
		str = get_new_line_cmd(str, i, size, str_good);
	return (str);
}

char	*ft_is_dollar2(char *str, t_control *control, int is_mal, int size)
{
	int		i;
	char	*str_good;
	char	*new_str;

	i = -1;
	while (str && str[++i])
	{
		i = check_unpair_chars(str, i);
		if (i == -1)
			break ;
		if (str[i] && str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
		{
			new_str = get_new_str(str, i, &size);
			str_good = ft_is_dollar3(control, new_str, &is_mal);
			str = ft_change_str_value(str_good, str, size, i);
			if (is_mal)
				free(str_good);
			is_mal = 0;
			free(new_str);
			i = -1;
			continue ;
		}
	}
	return (str);
}
