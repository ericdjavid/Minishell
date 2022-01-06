/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:59:10 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/05 18:28:10 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_beg(t_control *list, char *str)
{
	t_element	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (FAILURE);
	new->str = ft_strdup(str);
	new->next = list->first_export;
	new->index = 1;
	list->first_export = new;
	list->size++;
	return (SUCCESS);
}

void	ft_get_value(t_element *prev1, t_element *prev2, t_element *node2,
		t_element *node1)
{
	t_element	*tmp;

	tmp = NULL;
	if (prev1 != NULL)
		prev1->next = node2;
	if (prev2 != NULL)
		prev2->next = node1;
	if (node2->next == NULL)
	{
		node2->next = node1->next;
		node1->next = NULL;
	}
	else
	{
		tmp = node1->next;
		node1->next = node2->next;
		node2->next = tmp;
	}
}

t_element	*modify_value(t_element *node1, t_element *node2,
	t_element *prev1, t_element *prev2)
{
	if (prev1 == NULL)
		return (node2);
	else if (prev2 == NULL)
		return (node1);
	return (NULL);
}

t_element	*swap_elem(int pos1, int pos2, t_control *list, int i)
{
	t_element	*tmp;
	t_element	*node1;
	t_element	*node2;
	t_element	*prev1;
	t_element	*prev2;

	prev2 = NULL;
	node1 = NULL;
	prev1 = NULL;
	node2 = NULL;
	tmp = list->first_export;
	while (tmp && ++i <= list->size)
	{
		if (tmp->index == pos1 - 1)
			prev1 = tmp;
		if (tmp->index == pos1)
			node1 = tmp;
		if (tmp->index == pos2 - 1)
			prev2 = tmp;
		if (tmp->index == pos2)
			node2 = tmp;
		tmp = tmp->next;
	}
	ft_get_value(prev1, prev2, node2, node1);
	return (modify_value(node1, node2, prev1, prev2));
}

t_bool	is_ascii_ordered(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		while (str1[i] == str2[i])
			i++;
		if (str1[i] > str2[i])
			return (FALSE);
		return (TRUE);
	}
	if (!str2[i])
		return (TRUE);
	return (FALSE);
}
