/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:17:25 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/09 11:23:56 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_delete_in_list(t_element *first, char *str)
{
    t_element *tmp;

    tmp = first;
    while (tmp)
    {
        if(ft_strncmp(tmp->str, str, ft_strlen(tmp->str)) == 0)
           {
               printf("is in the fucking list\n");
               //delete
           } 
        if (tmp->next == NULL)
            break ;
        tmp = tmp->next;
    }

}

void    ft_delete_from_lists(t_control *control, char *str)
{
    ft_delete_in_list(control->first_env, str);
    ft_delete_in_list(control->first_env_var, str);
    ft_delete_in_list(control->first_export, str);
}

int ft_unset(t_control *control, char *str)
{
    char *neo_str;
    t_element *tmp;
    // (void)control;

    neo_str = ft_remove_quotes(str);
    tmp = ft_is_in_list(control, neo_str);
    if (tmp)
    {
        ft_delete_from_lists(control, neo_str);
        free(tmp);
        free(str);
    }
    return (1);
/*         
0    All name operands were successfully unset.
>0    At least one name could not be unset.
*/
}
