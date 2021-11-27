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
    t_element *first_env_var;

    first_env = ft_init();
    first_export = ft_init();
    first_env_var = ft_init();
    if ((!first_export) || (!first_env) || (!first_env_var))
        return (FAILURE);
    list->first_env = first_env;
    list->first_export = first_export;
    list->first_env_var = first_env_var;
    list->size = 0;
    list->size_env = 0;
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
    if (!first)
        return ;
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

void ft_add_new_var(t_control  *list)
{
    // if (!list->size_env)
    //     return ;
    // if (type == DEAL_EXPORT)
    // {
    //     return ;
    // }
    t_element *elm;

    elm = list->first_env_var;
    if (!elm)
        return ;
    while(elm)
    {
        add_end_list(elm->str, list->first_export);
        add_end_list(elm->str, list->first_env);
        if (elm->next == NULL)
            break ;
        elm = elm->next;
    } 
    return ;
}

int ft_get_new_var(t_control *list, char **newargv)
{
    int i;

    i = 0;
    while (newargv[++i])
    {
        list->size_env++;
        add_end_list(newargv[i], list->first_env_var);
        add_end_list(newargv[i], list->first_env);
        add_end_list(newargv[i], list->first_export);
    }
    ft_print_export(list->first_env_var);
    return (1);
}

/* Liste toutes les variables d’environnement dans l’ordre ascii. 
sous la forme : declare -x nom=”valeur” ou declare -x nom */
//TODO: add "declare -x [var]"
int ft_export(t_control *list, char **newargv)
{
    int i = 0;
    
    if (newargv[++i])
        return (ft_get_new_var(list, newargv));
    //TODO: add env_var
    printf(RED"ok\n" END);
    add_index(list->first_export);
    while (check_order(list) == FALSE)
        order_ascii(list);
    // ft_add_new_var(list);
    ft_print_export(list->first_export);
    // ft_print_export(list->first_env_var);
    free_all(list);
    return (1);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int ft_env(t_control *list)
{
    //TODO: add env_var
    // ft_add_new_var(list);
    ft_print_export(list->first_env);
    // ft_print_export(list->first_env_var);

    //TODO: free after
    free_all(list);
    return (1);
}