/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:51:08 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/18 19:01:03 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elms(t_element *first)
{
	t_element	*tmp;

	tmp = first;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		first = first->next;
		free(tmp->str);
		free(tmp->var_name);
		free(tmp);
		tmp = first;
	}
	return ;
}

void	free_all(t_control *control)
{
	if (control->first_env)
		free_elms(control->first_env);
	if (control->first_export)
		free_elms(control->first_export);
	if (control->first_env_var)
		free_elms(control->first_env_var);
	return ;
}
