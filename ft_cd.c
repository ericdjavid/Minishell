/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:39:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 18:20:26 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **newargv)
{
	if (ft_matlen(newargv) != 2)
		return (0);
	if (newargv[1][0] != '~') 
		chdir(newargv[1]);
	else
	{
		chdir(getenv("HOME"));
		newargv[1] += 2;
		chdir(newargv[1]);
		newargv[1] -= 2;
	}

	// TODO: changer la valeur de la variable PWD et OLDPWD de env
	return (1);
}