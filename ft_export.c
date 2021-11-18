/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:28:28 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/18 12:28:31 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *add_str(char *str)
{
    char    *tmp;
    int     i;
        
    i = 0;
    tmp = malloc(sizeof(char) * strlen(str) + 1);
    if (!tmp)
        return NULL;
    while (str[i] != '\0')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
    
}

void add_end_list(char *str, t_control *list)
{
    t_element *tmp;
    t_element *tmp2;

    if (!(list->first->str))
    {
        list->first->str = add_str(str);
        list->first->next = NULL;
        return ;
    }
    tmp = list->first;
    while (tmp->next)
        tmp = tmp->next;
    tmp2 = malloc(sizeof(*tmp));
    tmp2->str = add_str(str);
    tmp2->next = NULL;
    tmp->next = tmp2;
   return; 
}

t_control *ft_init()
{
    t_control *list; 
    t_element *first;

    list = malloc(sizeof(*list)); 
    first = malloc(sizeof(*first));
    if (!list || !first)
        return (NULL);
    list->first = first;
    first->str = NULL;
    first->next = NULL;
    return (list);
}

void    ft_print_export(t_element *first)
{
    t_element *tmp;

    tmp = first;
    while (tmp)
    {
        ft_printf_fd(1,"%s\n", tmp->str);
        if (tmp->next)
            tmp = tmp->next;
        else
            break ;
    }
    return ; 
}

/*
liste toutes les variables d’environnement dans l’ordre ascii. 
*/
int ft_export(t_control *list)
{
    ft_print_export(list->first);
    free_all(list);
    return (0);
}