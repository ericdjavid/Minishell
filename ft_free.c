/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:51:08 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/18 16:51:10 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_elms(t_element *first)
{
    t_element *tmp;

    tmp = first;
    while (tmp)
    {
        first = first->next;
        free(tmp->str);
        free(tmp);
        tmp = first;
    } 
    return ;
}

void free_all(t_control *control)
{
    if (control->first)
        free_elms(control->first);
    if (control)
        free(control);
    return ;
}