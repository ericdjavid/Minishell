/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:08:32 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/04 14:18:14 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_is_dollar3(t_control *control, char *new_str)
{
	char	*str_good;

	str_good = is_in_list(control->first_env, new_str);
	if (str_good == NULL)
		str_good = is_in_list(control->first_env_var, new_str);
	if (str_good == NULL && new_str[1] == '?')
		str_good = ft_itoa(g_status);
	return (str_good);
}

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
	i = 0;
	j = 0;
	while (str[i] && i < pos)
	{
		new[j] = str[i];
		j++;
		i++;
	}
	i += size;
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*ft_is_dollar2(char *str, t_control *control, int *modif)
{
	int		i;
	char	*str_good;
	char	*new_str;
	int		size;

	i = -1;
	size = 0;
	while (str && str[++i])
	{
		if (str[i] && str[i] == '\'' && no_unpair_char_before(str, i, '"'))
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] != '\'')
				break ;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
		{
			new_str = get_new_str(str, i, &size);
			str_good = ft_is_dollar3(control, new_str);
			if (str_good == NULL)
			{
				str = ft_strcut(str, size, i);
				//TODO : can t do it, need to modify value of $nothing to nothin in the string
				*modif = 0;
				free(new_str);
				i = -1;
				continue ;
			}
			free(new_str);
			if (str_good != NULL)
			{
				str = get_new_line_cmd(str, i, size, str_good);
				if (str[i + 1] == '?')
					free(str_good);
				i = -1;
				continue ;
			}
		}
	}
	return (str);
}

char	*get_new_line_cmd(char *str, int i, int size, char *str_good)
{
	char	*neo_line_cmd;
	int		j;
	int		k;

	neo_line_cmd = malloc(sizeof(char) * ((int)ft_strlen(str_good)
				+ (int)ft_strlen(str) - size + 1));
	j = -1;
	while (str[++j] && j < i)
		neo_line_cmd[j] = str[j];
	k = -1;
	while (str_good[++k] && k < (int)ft_strlen(str_good))
	{
		neo_line_cmd[j] = str_good[k];
		j++;
	}
	k = (i + size);
	while (str[k])
	{
		neo_line_cmd[j] = str[k];
		j++;
		k++;
	}
	free(str);
	neo_line_cmd[j] = '\0';
	return (neo_line_cmd);
}
