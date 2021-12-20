/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:59:10 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/20 14:57:03 by edjavid          ###   ########.fr       */
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

int swap_elem(int pos1, int pos2, t_control *list)
{
	t_element	*tmp;
	t_element	*node1;
	t_element	*node2;
	t_element	*prev1;
	t_element	*prev2;
	t_element	*tmp1;
	int			i;

	i = 0;
	prev1 = NULL;
	prev2 = NULL;
	node1 = NULL;
	node2 = NULL;
	tmp = list->first_export;
	if (pos1 == pos2)
		return (SUCCESS);
	if (pos1 <= 0 || pos1 > list->size || pos2 <= 0 || pos2 > list->size)
		return (FAILURE);
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
	if (prev1 != NULL)
		prev1->next = node2;
	if (prev2 != NULL)
		prev2->next = node1;
	if (node2->next == NULL)
	{
		tmp1 = node1->next;
		node2->next = node1->next;
		node1->next = NULL;
	}
	else
	{
		tmp1 = node1->next;
		node1->next = node2->next;
		node2->next = tmp1;
	}
	if (prev1 == NULL)
		list->first_export = node2;
	else if (prev2 == NULL)
		list->first_export = node1;
	add_index(list->first_export);
	return (SUCCESS);
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

int	order_ascii(t_control *list)
{
	t_element	*tmp;

	tmp = list->first_export;
	while (1)
	{
		if (tmp == NULL || tmp->next == NULL)
			break ;
		if (!is_ascii_ordered(tmp->str, tmp->next->str))
			swap_elem(tmp->index, tmp->next->index, list);
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
