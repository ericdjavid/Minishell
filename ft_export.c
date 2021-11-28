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
    tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
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

t_element *add_end_list2(char *str, t_element *first)
{
    t_element *tmp;
    t_element *tmp2;

    if (!(first->str))
    {
        first->str = add_str(str);

        printf(PINK "** added str |%s|\n"END, str);
        first->next = NULL;
        return first;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp2 = malloc(sizeof(*tmp));
        printf(RED "*** added str |%s|\n"END, str);
    tmp2->str = add_str(str);
    tmp2->next = NULL;
    tmp2->index = 0;
    tmp->next = tmp2;
    return tmp2; 
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
    return ;
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
    add_index(list->first_export);
    while (check_order(list) == FALSE)
        order_ascii(list);
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

int ft_get_new_var(t_control *list, char **newargv)
{
    int i;
    t_element *new;
    t_element *tmp;

    i = 0;
    tmp = list->first_env_var;
    while (newargv[++i])
    {
        list->size_env++;
        // list->first_env_var = add_end_list2(newargv[i], list->first_env_var);
        if (list->first_env_var->str == NULL)
        {
            list->first_env_var->str = ft_strdup(newargv[i]);
            printf(PINK "** added str |%s|\n"END, newargv[i]);
            continue ;
        }
        while (tmp->next != NULL)
            tmp = tmp->next;
        new = malloc(sizeof(*new));
        if (!new)
            return (FAILURE);
        new->str = ft_strdup(newargv[i]);
        printf(RED "** added str |%s|\n"END, newargv[i]);
        new->next = NULL;
        new->index = i;   
        tmp->next = new;
    }
    return (1);
}

int ft_add_new_var(t_control  *list, int type)
{
    t_element *tmp;

    tmp = list->first_env_var;
    if (!tmp)
        return(FAILURE);
    while (tmp && tmp->str)
    {
        //TODO: add " " if =
        if (type == DEAL_EXPORT)
            add_end_list(tmp->str, list->first_export);
        else
            add_end_list(tmp->str, list->first_env);
        if (tmp->next)
            tmp = tmp->next;
        else
            break;
    }
    return (SUCCESS);
}

/* Liste toutes les variables d’environnement dans l’ordre ascii. 
sous la forme : declare -x nom=”valeur” ou declare -x nom */
//TODO: add "declare -x [var]"
//TODO: add env_var
int ft_export(t_control *list, char **newargv)
{
    (void)newargv;
    ft_add_new_var(list, DEAL_EXPORT);

    ft_print_export(list->first_export);

    //TODO : declare -x [var]
    free_all(list);
    return (1);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int ft_env(t_control *list)
{
    //TODO: add env_var
    // ft_add_new_var(list);
    ft_add_new_var(list, DEAL_ENV);
    ft_print_export(list->first_env);
    // ft_print_export(list->first_env_var);

    //TODO: free after
    free_all(list);
    return (1);
}