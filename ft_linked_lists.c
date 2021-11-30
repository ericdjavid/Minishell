/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:18:13 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/27 15:18:14 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_index(t_element *elem)
{
    int i = 0;
    while (elem->next)
    {
        elem->index = ++i;
        elem = elem->next;
    }
    elem->index = ++i;
    return;
}