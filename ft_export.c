/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:28:28 by edjavid           #+#    #+#             */
/*   Updated: 2021/11/21 16:49:08 by abrun            ###   ########.fr       */
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

void add_end_list(char *str, t_element *first)
{
    t_element *tmp;
    t_element *tmp2;

    if (!(first->str))
    {
        first->str = add_str(str);
        first->next = NULL;
        return ;
    }
    tmp = first;
    while (tmp->next)
        tmp = tmp->next;
    tmp2 = malloc(sizeof(*tmp));
    tmp2->str = add_str(str);
    tmp2->next = NULL;
    tmp->next = tmp2;
   return; 
}

t_element *ft_init()
{
    t_element *first;

    first = malloc(sizeof(*first));
    if (!first)
        return (NULL);
    first->str = NULL;
    first->next = NULL;
    return (first);
}

int ft_init_list(t_control *list, char **envp)
{
    int i;
    t_element *first_env;
    t_element *first_export;

    first_env = ft_init();
    first_export = ft_init();
    if (!first_export || !first_env)
        return (FAILURE);
    list->first_env = first_env;
    list->first_export = first_export;
	i = -1;
    while (envp[++i])
    {
		add_end_list(envp[i], list->first_export);	
		add_end_list(envp[i], list->first_env);	
    }
    return (SUCCESS);
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

t_element *swap_first(t_element *elem)
{
    t_element *tmp;

    if (!elem)
        return (NULL);
    tmp = elem->next;
    elem->next = tmp->next; 
    tmp->next = elem;
    elem = tmp;
    printf(RED"tmp is now \n|%s|\n and next is \n|%s|\n",tmp->str, tmp->next->str);
    return (tmp);
}

/* Liste toutes les variables d’environnement dans l’ordre ascii. 
sous la forme : declare -x nom=”valeur” ou declare -x nom */
int ft_export(t_control *list)
{
    //be able to be piped
    // t_element *tmp;   
    
    // tmp = list->first_export;

    // ft_print_export(list->first_export);
    // list->first_export = swap_elem(list->first_export);
    // printf("first is |%s|\n", list->first_export->str);
    // printf("first letter is of tmp is |%c| with value |%d| and tmp->next is |%c| value |%d|", tmp->str[0],tmp->str[0], tmp->next->str[0], tmp->next->str[0]);

    // while (tmp->next)
    // {
    //     // printf("first letter is |%d| and the other is |%d|", tmp->str[0], tmp->next->str[0]);
    //     if (tmp->str[0] < tmp->next->str[0])
    //     {
    //         swap_elem(tmp);
    //     }
    //     tmp = tmp->next;
    // }
    // ft_print_export(list->first_export);
    free_all(list);
    return (FAILURE);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int ft_env(t_control *list)
{
    //be able to be piped
    ft_print_export(list->first_env);
    free_all(list);
    return (1);
}