/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:26:43 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/14 10:58:19 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_in_child(char **new_env)
{
	if (new_env)
		free_matc(new_env);
}

void	ft_remove_from_list(t_element *to_supp, t_element *first)
{
	if (to_supp == NULL)
		return ;
	if (to_supp->next == NULL)
		ft_delete_last(first);
	else
		ft_replace_str(to_supp);
	return ;
}

int	count_amout(char *str, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

char	*ft_is_dollar3(t_control *control, char *new_str, int *is_mal)
{
	char	*str_good;

	str_good = is_in_list(control->first_env, new_str);
	if (str_good == NULL)
		str_good = is_in_list(control->first_env_var, new_str);
	if (str_good == NULL && new_str[1] == '?')
	{
		*is_mal = 1;
		str_good = ft_itoa(g_status);
	}
	return (str_good);
}

char	*get_new_line_cmd(char *str, int i, int size, char *str_good)
{
	char	*neo_line_cmd;
	int		j;
	int		k;

	neo_line_cmd = malloc(sizeof(char) * ((int)ft_strlen(str_good)
				+ (int)ft_strlen(str) - size + 1));
	if (!neo_line_cmd)
		return (NULL);
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
		neo_line_cmd[j++] = str[k++];
	free(str);
	neo_line_cmd[j] = '\0';
	return (neo_line_cmd);
}
