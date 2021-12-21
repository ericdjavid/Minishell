/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:14:53 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/21 17:07:29 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_deal_SHLVL(t_control *control)
{
	t_element	*tmp;
	// int			x;
	char		*c;

	tmp = ft_good_find_in_list(control->first_env, "SHLVL");
	if (!tmp)
		return ;
	// x = ft_atoi(ft_get_good_str(tmp->str));
	c = ft_get_good_str(tmp->str);
	c[0] = c[0] + 1;
	tmp = ft_good_find_in_list(control->first_export, "SHLVL");
	if (!tmp)
		return ;
	// x = ft_atoi(ft_get_good_str(tmp->str));
	c = ft_get_good_str(tmp->str);
	c[1] = c[1] + 1;
}

t_element	*ft_init(void)
{
	t_element	*first;

	first = malloc(sizeof(*first));
	if (!first)
		return (NULL);
	first->str = NULL;
	first->var_name = NULL;
	first->next = NULL;
	first->index = 0;
	return (first);
}
