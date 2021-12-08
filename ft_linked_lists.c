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

char *ft_get_good_str(char *str)
{
    int i;

    i = 0;
    while (*str != '=' && *str != '\0')
    {
        str++;
        i++;
    }
    if (*str == '=')
        str++;
    if (*str == '\0')
        return (NULL);
    // printf("new str is |%s|", str);
    return (str);  
}

char    *ft_get_parsed_env(char *str)
{
    int     i;
    char    *tmp;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '\0')
        return (NULL);
    tmp = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (str[i] && str[i] != '=')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char *is_in_list(t_element *first, char *str)
{
    t_element *tmp;
    char    *new_str;
    char    *wip_str;

    new_str = ++str;
    tmp = first;
    while (tmp)
    {
        wip_str = ft_get_parsed_env(tmp->str);
        if (ft_strncmp(wip_str, new_str, ft_strlen(wip_str)) == 0)
        {
            free(wip_str);
            return (ft_get_good_str(tmp->str));
        }
        else
            free(wip_str);
        if (tmp == NULL)
            break ;
        tmp = tmp->next;
    }
    return (FALSE);
}

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