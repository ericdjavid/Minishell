/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:10:49 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/20 15:11:27 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_new_var(t_control *list, int type)
{
	t_element	*tmp;

	tmp = list->first_env_var;
	if (!tmp)
		return (FAILURE);
	while (tmp && tmp->str)
	{
		if (type == DEAL_EXPORT)
			add_end_list(tmp->str, list->first_export, DEAL_EXPORT, list);
		else
			add_end_list(tmp->str, list->first_env, 0, list);
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
	ft_add_new_var(list, DEAL_EXPORT);
	ft_print_export(list->first_export, TRUE);
	free_all(list);
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
	free(tmp);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int	ft_env(t_control *list)
{
	ft_add_new_var(list, DEAL_ENV);
	ft_print_export(list->first_env, FALSE);
	free_all(list);
	return (1);
}
