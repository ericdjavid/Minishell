/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 14:03:18 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/24 17:06:32 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_stuff(t_element *first, char *str)
{
	t_element	*tmp;

	if (!first)
	{
		printf("list is empty !\n");
		return (FAILURE);
	}
	tmp = first;
	printf(YELLOW"---LIST %s---\n", str);
	while (tmp != NULL)
	{
		printf("[%s]\n", tmp->str);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	printf("----------\n" END);
	return (1);
}

void	ft_replace_str(t_element *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->next == NULL)
	{
		free(tmp->str);
		free(tmp->var_name);
		free(tmp);
	}
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

//if = in uset word, print "not a valid identifier"
int	ft_unset(t_control *control, char **newargv)
{
	t_element	*tmp;
	int			i;

	i = 0;
	while (newargv[++i])
	{
		ft_print_stuff(control->first_env_var, "before unset");
		tmp = ft_good_find_in_list(control->first_env_var, newargv[i]);
		if (tmp)
		{
			ft_remove_from_env(tmp, control);
			ft_print_stuff(control->first_env_var, "after unset");
			continue ;
		}
		tmp = ft_good_find_in_list(control->first_env, newargv[i]);
		if (tmp == control->first_env)
		{
			if (control->first_env->next)
				control->first_env = control->first_env->next;
			free(tmp->str);
			free(tmp->var_name);
			free(tmp);
		}
		else
		{
			if (tmp && tmp->next == NULL)
				ft_delete_last(control->first_env);
			else if (tmp)
				ft_replace_str(tmp);
		}
		tmp = ft_good_find_in_list(control->first_export, newargv[i]);
		if (tmp == control->first_export)
		{
			if (control->first_export->next)
				control->first_export = control->first_export->next;
			free(tmp->str);
			free(tmp->var_name);
			free(tmp);
		}
		else
		{
			if (tmp && tmp->next == NULL)
				ft_delete_last(control->first_export);
			else if (tmp)
				ft_replace_str(tmp);
		}
	}
	return (1);
}
/*
0    All name operands were successfully unset.
>0    At least one name could not be unset.
*/
