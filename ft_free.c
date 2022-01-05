/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:51:08 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/05 15:33:50 by edjavid          ###   ########.fr       */
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

void	free_elm(t_element *tmp)
{
	free(tmp->str);
	free(tmp->var_name);
	free(tmp);
}

void	free_elms(t_element *first)
{
	t_element	*tmp;

	tmp = first;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		first = first->next;
		free_elm(tmp);
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
	{
		ft_print_stuff(control->first_env_var, "lolcat");
		free_elms(control->first_env_var);
		// free(control->first_env_var);
	}
	return ;
}
