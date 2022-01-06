/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii_order2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:27:38 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/05 18:28:02 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	order_ascii(t_control *list)
{
	t_element	*tmp;
	t_element	*tmp2;
	int			i;

	i = 0;
	tmp2 = list->first_export;
	tmp = list->first_export;
	while (1)
	{
		if (tmp == NULL || tmp->next == NULL)
			break ;
		if (!is_ascii_ordered(tmp->str, tmp->next->str))
		{
			tmp2 = swap_elem(tmp->index, tmp->next->index, list, i);
			if (tmp2)
				list->first_export = tmp2;
			add_index(list->first_export);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

t_bool	check_order(t_control *list)
{
	t_element	*tmp;

	tmp = list->first_export;
	while (tmp->next)
	{
		if (is_ascii_ordered(tmp->str, tmp->next->str) == FALSE)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
