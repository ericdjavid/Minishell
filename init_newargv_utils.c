/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:35:36 by abrun             #+#    #+#             */
/*   Updated: 2021/12/23 13:54:24 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_split_in_newargv(char **split, char ***newargv, int *c)
{
	int	c_2;

	c_2 = 0;
	while (split[*c] && ft_strncmp(split[*c], "|", ft_strlen(split[*c])))
	{
		if (ft_strncmp(split[*c], "exit", ft_strlen(split[*c])))
		{
			newargv[0][c_2] = split[*c];
			c_2++;
		}
		else
			free(split[*c]);
		*c += 1;
		if (split[*c] && !ft_strncmp(split[*c], "|", ft_strlen(split[*c]))
			&& !c_2)
		{
			free(split[*c]);
			*c += 1;
		}
	}
	if (!c_2)
		newargv[0][0] = 0;
	return (c_2);
}
