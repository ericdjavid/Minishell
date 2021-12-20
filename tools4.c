/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:59:06 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/20 15:04:44 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_dollar(char **str, t_control *control)
{
	int		i;
	char	*str_good;

	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '$' && str[i][1] != ' '
			&& str[i][1] && str[i][1] != '?')
		{
			str_good = is_in_list(control->first_env, str[i]);
			if (str_good == NULL)
				str_good = is_in_list(control->first_env_var, str[i]);
			if (str_good != NULL)
			{
				free(str[i]);
				str[i] = ft_strdup(str_good);
			}
			else
			{
				free(str[i]);
				str[i] = NULL;
			}
		}
	}
	return ;
}

char	*get_new_str(char *str, int i, int *size)
{
	int		j;
	int		k;
	char	*new_str;

	j = i + 1;
	while (str[j] && str[j] != '\0' && str[j] != '$' && str[j] != ' '
		&& str[j] != '\"')
		j++;
	*size = j - i;
	new_str = malloc(sizeof(char) * (j - i + 1));
	k = 0;
	new_str[k] = '$';
	i++;
	k++;
	while (str[i] && str[i] != '\0' && str[i] != '$'
		&& str[i] != ' ' && str[i] != '\"')
	{
		new_str[k] = str[i];
		k++;
		i++;
	}
	new_str[k] = '\0';
	return (new_str);
}

void	ft_remove_from_env(t_element *to_supp, t_control *control)
{
	if (to_supp == control->first_env_var)
		ft_remove_first_env(control);
	else if (to_supp->next == NULL)
		ft_delete_last(control->first_env_var);
	else
		ft_replace_str(to_supp);
	return ;
}

void	ft_delete_last(t_element *first)
{
	t_element	*tmp;

	tmp = first;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next->str);
	free(tmp->next->var_name);
	free(tmp->next);
	tmp->next = NULL;
	return ;
}
