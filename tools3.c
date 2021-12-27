/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:08:32 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/27 14:06:43 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_bad_entries(char *str)
{
	int	sq;
	int	dq;
	int	i;

	if (!str)
		return (TRUE);
	sq = 0;
	dq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			sq++;
		if (str[i] == '\"')
			dq++;
	}
	if (sq % 2 != 0 || dq % 2 != 0)
		return (TRUE);
	return (FALSE);
}

char	*ft_is_dollar3(t_control *control, char *new_str)
{
	char	*str_good;

	str_good = is_in_list(control->first_env, new_str);
	if (str_good == NULL)
		str_good = is_in_list(control->first_env_var, new_str);
	if (str_good == NULL && new_str[1] == '?')
		str_good = ft_itoa(status);
	return (str_good);
}

char	*ft_is_dollar2(char *str, t_control *control)
{
	int		i;
	char	*str_good;
	char	*new_str;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
		{
			new_str = get_new_str(str, i, &size);
			str_good = ft_is_dollar3(control, new_str);
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
