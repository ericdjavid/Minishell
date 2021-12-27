/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:11:48 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/26 18:19:15 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_element *first, t_bool bool)
{
	t_element	*tmp;

	tmp = first;
	if (!first)
		return ;
	while (tmp)
	{
		if (bool == TRUE)
			ft_printf_fd(1, "declare -x ");
		ft_printf_fd(1, "%s\n", tmp->str);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return ;
}

void	ft_process_str(char **arr_str, t_control *list, char *new_str)
{
	int	i;

	i = 0;
	while (arr_str[++i])
	{
		new_str = ft_get_dollar_var(arr_str[i], list);
		free(arr_str[i]);
		arr_str[i] = ft_strdup(new_str);
		if (new_str)
			free(new_str);
	}
}

char	*ft_deal_dollar(char *str, t_control *list)
{
	char	*new_str;
	char	**arr_str;
	char	*ret;
	char	*ret2;
	int		i;

	new_str = NULL;
	if (!(ft_strchr(str, '$')))
		return (NULL);
	arr_str = ft_split(str, "$");
	if (!arr_str)
		return (NULL);
	ft_process_str(arr_str, list, new_str);
	i = 0;
	ret = NULL;
	while (arr_str[++i])
		ret = ft_strjoin(ret, arr_str[i]);
	free_matc(arr_str);
	ret2 = ft_remove_quotes(ret);
	free(ret);
	return (ret2);
}

int	ft_get_new_var(t_control *list, char **newargv)
{
	int			i;
	t_element	*new;
	t_element	*tmp;
	char		*retreat;
	char		*var_name;

	i = 0;
	retreat = NULL;
	var_name = NULL;
	while (newargv[++i])
	{
		if (retreat)
			free (retreat);
		retreat = NULL;
		retreat = ft_deal_dollar(newargv[i], list);
		if (retreat == NULL)
			retreat = ft_remove_simple_quotes(newargv[i]);
		if (!(ft_check_position('$', '=', newargv[i])) || (newargv[i][0] <= 'Z'
			&& newargv[i][0] >= 'A') || (newargv[i][0] == '='
			|| ((retreat[0] <= '9') && (retreat[0] >= '0'))))
		{
			ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
			continue ;
		}
		var_name = add_var_name(retreat);
		tmp = elem_in_list(list->first_env_var, var_name);
		if ((ft_is_space_before_qual(retreat))
			|| (is_quest(retreat) == TRUE))
		{
			ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
			free(tmp);
			continue ;
		}
		if (tmp)
		{
			if (!ft_strchr(retreat, '='))
				continue ;
			free(tmp->str);
			tmp->str = ft_strdup(retreat);
			ft_remove_from_list(elem_in_list(list->first_export, var_name), list->first_export);
			ft_remove_from_list(elem_in_list(list->first_env, var_name), list->first_env);
			free(var_name);
			continue ;
		}
		if (list->first_env_var->str == NULL)
		{
			list->first_env_var->str = ft_strdup(retreat);
			list->first_env_var->var_name
				= add_var_name(list->first_env_var->str);
			list->first_env_var->next = NULL;
			free(var_name);
			continue ;
		}
		tmp = list->first_env_var;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new = malloc(sizeof(*new));
		if (!new)
			return (FAILURE);
		new->str = ft_strdup(retreat);
		new->var_name = add_var_name(new->str);
		new->next = NULL;
		new->index = i;
		tmp->next = new;
		free(var_name);
	}
	if (retreat)
		free (retreat);
	ft_add_new_var(list, DEAL_EXPORT);
	ft_add_new_var(list, DEAL_ENV);
	return (1);
}
