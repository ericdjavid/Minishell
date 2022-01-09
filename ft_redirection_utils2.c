/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:19:31 by abrun             #+#    #+#             */
/*   Updated: 2022/01/05 17:20:01 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_other_wrout(char **newargv)
{
	int	c;

	c = 0;
	while (newargv[c])
	{
		if (which_redirection(newargv[c]))
			return (1);
		c++;
	}
	return (0);
}
