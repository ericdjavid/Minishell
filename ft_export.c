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
    tmp2->index = 0;
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
    first->index = 0;
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
    list->size = 0;
	i = -1;
    while (envp[++i])
    {
        list->size++;
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

/* Liste toutes les variables d’environnement dans l’ordre ascii. 
sous la forme : declare -x nom=”valeur” ou declare -x nom */
int ft_export(t_control *list)
{
    add_index(list->first_export);
    while (check_order(list) == FALSE)
        order_ascii(list);
    ft_print_export(list->first_export);
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