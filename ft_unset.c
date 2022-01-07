/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 14:03:18 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/07 19:38:20 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_str(t_element *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->next == NULL)
		free_elm(tmp);
	while (tmp)
	{
		if (tmp->next->next == NULL)
			break ;
		free(tmp->str);
		free(tmp->var_name);
		tmp->str = ft_strdup(tmp->next->str);
		tmp->var_name = ft_strdup(tmp->next->var_name);
		tmp = tmp->next;
	}
	free(tmp->str);
	free(tmp->var_name);
	tmp->str = ft_strdup(tmp->next->str);
	tmp->var_name = ft_strdup(tmp->next->var_name);
	if (tmp->next->str)
		free(tmp->next->str);
	if (tmp->next->var_name)
		free(tmp->next->var_name);
	free(tmp->next);
	tmp->next = NULL;
	return ;
}

t_element	*ft_good_find_in_list(t_element *first, char *noequal_str)
{
	t_element	*tmp;

	tmp = first;
	while (tmp && tmp->var_name)
	{
		if (ft_strncmp(tmp->var_name, noequal_str,
				ft_strlen(noequal_str)) == 0)
			return (tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_unset_export(t_control *control, char *newargv)
{
	t_element	*tmp;

	tmp = ft_good_find_in_list(control->first_export, newargv);
	if (tmp == control->first_export)
	{
		if (control->first_export->next)
			control->first_export = control->first_export->next;
		free_elm(tmp);
	}
	else
	{
		if (tmp && tmp->next == NULL)
			ft_delete_last(control->first_export);
		else if (tmp)
			ft_replace_str(tmp);
	}
}

void	ft_unset_env(t_control *control, char *newargv)
{
	t_element	*tmp;

	tmp = ft_good_find_in_list(control->first_env, newargv);
	if (tmp == control->first_env)
	{
		if (control->first_env->next)
			control->first_env = control->first_env->next;
		free_elm(tmp);
	}
	else
	{
		if (tmp && tmp->next == NULL)
			ft_delete_last(control->first_env);
		else if (tmp)
			ft_replace_str(tmp);
	}
}

int	ft_unset(t_control *control, char **newargv)
{
	t_element	*tmp;
	int			i;

	i = 0;
	while (newargv[++i])
	{
		if (ft_strchr(newargv[i], '='))
			ft_printf_fd(1, "\'%s\' : not a valid identifier\n", newargv[i]);
		tmp = ft_good_find_in_list(control->first_env_var, newargv[i]);
		if (tmp)
		{
			ft_remove_from_list(elem_in_list(control->first_export,
					tmp->var_name), control->first_export);
			ft_remove_from_list(elem_in_list(control->first_env,
					tmp->var_name), control->first_env);
			ft_remove_from_env(tmp, control);
			continue ;
		}
		ft_unset_env(control, newargv[i]);
		ft_unset_export(control, newargv[i]);
	}
	return (1);
}
