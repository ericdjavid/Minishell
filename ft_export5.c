/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:23:17 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/10 12:14:52 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tmp(char *retreat, t_element *tmp, t_control *list, char *var_name)
{
	char	*nodq;

	if (!ft_strchr(retreat, '='))
	{
		free(var_name);
		return (1);
	}
	free(tmp->str);
	nodq = ft_strdup(retreat);
	tmp->str = ft_remove_quotes(nodq);
	free(nodq);
	ft_remove_from_list(elem_in_list(list->first_export, var_name),
		list->first_export);
	ft_remove_from_list(elem_in_list(list->first_env, var_name),
		list->first_env);
	free(var_name);
	return (1);
}

int	get_not_valid(char *retreat, t_element *tmp)
{
	if ((ft_is_space_before_qual(retreat))
		|| (is_quest(retreat) == TRUE))
	{
		ft_printf_fd(1, RED"Minishell: export: \"%s\": not a valid identifier\n"
			END, retreat);
		free(tmp);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	mdval(t_element *elem, char *str, int type)
{
	free(elem->str);
	if (type == DEAL_EXPORT)
		elem->str = add_str2(str, DEAL_EXPORT);
	else
		elem->str = ft_strdup(str);
	return ;
}

int	ft_get_new_var2(char *var_name, char *retreat, t_control *list, int i)
{
	t_element	*tmp;

	var_name = add_var_name(retreat);
	tmp = elem_in_list(list->first_env_var, var_name);
	if (get_not_valid(retreat, tmp))
	{
		free(var_name);
		return (FAILURE);
	}
	if (tmp && get_tmp(retreat, tmp, list, var_name))
		return (FAILURE);
	if (tmp == NULL && elem_in_list(list->first_export, var_name))
	{
		mdval(elem_in_list(list->first_export, var_name), retreat, DEAL_EXPORT);
		mdval(elem_in_list(list->first_env, var_name), retreat, DEAL_ENV);
		free(var_name);
		return (SUCCESS);
	}
	if (list->first_env_var->str == NULL && get_f(list, var_name, retreat))
		return (FAILURE);
	if (ft_assign(tmp, list, retreat, i))
		return (FAILURE);
	free(var_name);
	return (SUCCESS);
}

int	ft_get_new_var(t_control *list, char **newargv)
{
	int			i;
	char		*retreat;
	char		*var_name;

	i = 0;
	var_name = NULL;
	retreat = NULL;
	while (newargv[++i])
	{
		if (retreat)
			free (retreat);
		retreat = ft_remove_simple_quotes(newargv[i]);
		if (process_retreat(newargv[i], retreat) == FAILURE)
			continue ;
		if (ft_get_new_var2(var_name, retreat, list, i))
			continue ;
	}
	if (retreat)
		free (retreat);
	ft_add_new_var(list, DEAL_EXPORT);
	ft_add_new_var(list, DEAL_ENV);
	return (1);
}
