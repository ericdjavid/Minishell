/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:11:48 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/06 16:35:56 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_f(t_control *list, char *var_name, char *retreat)
{
	char	*nodq;

	nodq = ft_strdup(retreat);
	list->first_env_var->str = ft_remove_quotes(nodq);
	list->first_env_var->var_name
		= add_var_name(list->first_env_var->str);
	list->first_env_var->next = NULL;
	free(nodq);
	free(var_name);
	return (1);
}

int	add_end_list(char *str, t_element *first, int type)
{
	t_element	*tmp;
	t_element	*tmp2;
	char		*str_new;

	str_new = add_str2(str, type);
	if (!str_new)
		return (FAILURE);
	if (!(first->str))
	{
		first->str = str_new;
		first->var_name = add_var_name(str_new);
		first->next = NULL;
		return (SUCCESS);
	}
	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = malloc(sizeof(*tmp));
	if (!tmp2)
		return (0);
	tmp2->str = str_new;
	tmp2->var_name = add_var_name(str_new);
	tmp2->next = NULL;
	tmp->next = tmp2;
	return (SUCCESS);
}

int	add_str4(char *str, int type, t_bool is_equal, char *tmp)
{
	int	k;
	int	j;
	int	i;

	j = 0;
	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_equal == TRUE && type == DEAL_EXPORT && str[i] == '=' && k == 0)
		{
			tmp[j] = str[i];
			tmp[++j] = '\"';
			i++;
			j++;
			k = 1;
			continue ;
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	return (j);
}

void	add_str3(int type, t_bool is_equal, char *str, char *tmp)
{
	int	j;

	j = add_str4(str, type, is_equal, tmp);
	if (is_equal == TRUE && type == DEAL_EXPORT)
	{
		tmp[j] = '\"';
		j++;
	}
	tmp[j] = '\0';
}

char	*add_str2(char *str, int type)
{
	char	*tmp;
	int		i;
	t_bool	is_equal;

	i = -1;
	is_equal = FALSE;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '=')
			is_equal = TRUE;
	}
	if (type == DEAL_ENV && is_equal == FALSE)
		return (NULL);
	if (is_equal == TRUE && type == DEAL_EXPORT)
		tmp = malloc(sizeof(char) * (ft_strlen(str) + 1 + 500));
	if (!tmp)
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	add_str3(type, is_equal, str, tmp);
	return (tmp);
}
