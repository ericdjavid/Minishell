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

/*
liste toutes les variables d’environnement dans l’ordre ascii. 
*/
int ft_export(char **newarg)
{
    int i = 0;
    while (newarg[i])
    {
        ft_printf_fd(1, "%s\n", newarg[i]);
        i++;
    }
    
    return 1;
}