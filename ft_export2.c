/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:10:49 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/26 14:17:20 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_new_var(t_control *list, int type)
{
	t_element	*tmp;

	tmp = list->first_env_var;
	if (!tmp)
		return (FAILURE);

	// not working when modifying value
	while (tmp && tmp->str)
	{
		if (elem_in_list(list->first_env, tmp->var_name))
		{
			printf("is in list !\n");
			if (tmp->next)
			{
				tmp = tmp->next;
				continue ;
			}
			else
				break ;
		}
		list->size++;
		if (type == DEAL_EXPORT)
			add_end_list(tmp->str, list->first_export, DEAL_EXPORT);
		else
			add_end_list(tmp->str, list->first_env, 0);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (SUCCESS);
}

/* Liste toutes les variables d’environnement dans l’ordre ascii.
sous la forme : declare -x nom=”valeur” ou declare -x nom */
int	ft_export(t_control *list, char **newargv)
{
	(void)newargv;
	if (!ft_strncmp(newargv[0], "export",
				ft_strlen(newargv[0]))
			&& newargv[1])
		ft_get_new_var(list, newargv);
	else
	{
		printf("print_export\n");
		// ft_print_stuff(list->first_env_var, "new env arr");
		// ft_add_new_var(list, DEAL_EXPORT);
		ft_print_export(list->first_export, TRUE);
	}
	return (1);
}

void	ft_remove_first_env(t_control *control)
{
	t_element	*tmp;

	if (control->first_env_var == NULL)
		return ;
	tmp = control->first_env_var;
	if (control->first_env_var->next)
		control->first_env_var = control->first_env_var->next;
	free(tmp->var_name);
	free(tmp->str);
	tmp->var_name = NULL;
	tmp->str  = NULL;
	// free(tmp);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int	ft_env(t_control *list)
{
	(void)list;
	ft_print_stuff(list->first_env_var, "str" );
	// ft_add_new_var(list, DEAL_ENV);
	ft_print_export(list->first_env, FALSE);
	return (1);
}
