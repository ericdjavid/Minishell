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

//TODO: when creating a new env with " ", bad behavior (double quotes)
char *add_str2(char *str, int type)
{
    char    *tmp;
    int     i;
    int     j;
    t_bool  is_equal;
        
    i = 0;
    j = 0;
    is_equal = FALSE;
    tmp = NULL;
    while (str[i])
    {
        if (str[i] == '=')
            is_equal = TRUE;
        i++;
    }
    if (type == DEAL_ENV && is_equal == FALSE)
        return (NULL);
    if (is_equal == TRUE && type == DEAL_EXPORT)
        tmp = malloc(sizeof(char) * ft_strlen(str) + 1 + 2);
    // if (ft_get_quotes(str) > 0)
    // {
    //     str = move_quotes(str);
    //     tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
    // }
    if (!tmp)
        tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
    // else
        // tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!tmp)
        return NULL;
    i = 0;
    while (str[i] != '\0')
    {
        if (is_equal == TRUE && type == DEAL_EXPORT && str[i] == '=')
        {
            tmp[j] = str[i];
            tmp[++j] = '\"';
            i++;
            j++;
            continue ;
        }
        tmp[j] = str[i];
        i++;
        j++;
    }
    if (is_equal == TRUE && type == DEAL_EXPORT)
    {
        tmp[j] = '\"';
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
    
}

int add_end_list(char *str, t_element *first, int type)
{
    t_element   *tmp;
    t_element   *tmp2;
    char        *str_new;

    str_new = add_str2(str, type);
    if (!str_new)
        return (FAILURE);
    if (!(first->str))
    {
        first->str = str_new;
        first->next = NULL;
        return (SUCCESS);
    }
    tmp = first;
    while (tmp->next)
        tmp = tmp->next;
    tmp2 = malloc(sizeof(*tmp));
    tmp2->str = str_new;
    tmp2->next = NULL;
    tmp2->index = 0;
    tmp->next = tmp2;
    return (SUCCESS);
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
		add_end_list(envp[i], list->first_export, 0);	
		add_end_list(envp[i], list->first_env, 0);	
    }
    add_index(list->first_export);
    while (check_order(list) == FALSE)
        order_ascii(list);
    return (SUCCESS);
}

void    ft_print_export(t_element *first, t_bool bool)
{
    t_element *tmp;

    tmp = first;
    if (!first)
        return ;
    while (tmp)
    {
        if (bool == TRUE)
            ft_printf_fd(1, "export ");
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
    //TODO: IF VAR ALREADY EXISTS, modify value
    //TODO: IF NAME ALREADY EXIST, do nothing
    //TODO: IF VALUE AFFECTED TO VAR with same name, modify it
    //TODO: CANNOT START WITH NUMBER
        list->size_env++;
        if (list->first_env_var->str == NULL)
        {
            list->first_env_var->str = ft_strdup(newargv[i]);
            continue ;
        }
        while (tmp->next != NULL)
            tmp = tmp->next;
        new = malloc(sizeof(*new));
        if (!new)
            return (FAILURE);
        new->str = ft_strdup(newargv[i]);
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
        {
            add_end_list(tmp->str, list->first_export, DEAL_EXPORT);
        }
        else
        {
            add_end_list(tmp->str, list->first_env, 0);
        }
        if (tmp->next)
            tmp = tmp->next;
        else
            break;
    }
    return (SUCCESS);
}

// EXPORT BUGS
//TODO: when creating already existing env it should modify it and not create another one


//TODO: problem with spacing 

/* Liste toutes les variables d’environnement dans l’ordre ascii. 
sous la forme : declare -x nom=”valeur” ou declare -x nom */
int ft_export(t_control *list, char **newargv)
{
    (void)newargv;
    ft_add_new_var(list, DEAL_EXPORT);

    ft_print_export(list->first_export, TRUE);
    free_all(list);
    return (1);
}

/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int ft_env(t_control *list)
{
    ft_add_new_var(list, DEAL_ENV);
    ft_print_export(list->first_env, FALSE);

    free_all(list);
    return (1);
}