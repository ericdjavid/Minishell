/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:38:14 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 10:43:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// TODO: faire les echos avec '$var' et "$var"

int	ft_echo(char **newargv)
{
	char	c;

	c = 0;
	if (ft_matlen(newargv) == 1)
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (!ft_strncmp(newargv[1], "-n", 2))
	{
		write_newargv(newargv, 2);
	}
	else
	{
		write_newargv(newargv, 1);
	}
	write(1, &c, 1);
	return (1);
}

void	write_newargv(char **newargv, int c)
{
	int	ret;

	ret = c;
	while (newargv[c])
	{
		write(1, newargv[c], ft_strlen(newargv[c]));
		c++;
		if (newargv[c])
			write(1, " ", 1);
	}
	if (ret == 1)
		write(1, "\n", 1);
}
