/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:38:14 by abrun             #+#    #+#             */
/*   Updated: 2021/12/23 17:31:28 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: echo truc | cat | cat | cat -e | cat -e
//  ^@
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
		while (check_echoArg(newargv[1 + c])
			c++;
		write_newargv(newargv, 2 + c);
	}
	else
	{
		write_newargv(newargv, 1);
	}
	write(1, &c, 1);
	status = 0;
	return (1);
}

void	write_newargv(char **newargv, int c)
{
	int	ret;

	ret = c;
	while (newargv[c])
	{
		if (!ft_strncmp(newargv[c], "$?", ft_strlen(newargv[c])))
			ft_putnbr_fd(status, 1);
		else
			write(1, newargv[c], ft_strlen(newargv[c]));
		c++;
		if (newargv[c])
			write(1, " ", 1);
	}
	if (ret == 1)
		write(1, "\n", 1);
}

int	check_echoArg(char *newargv)
{
	if (*newargv == '-')
	{
		newargv++;
		while (*newargv && *newargv == 'n')
			newargv++;
	}
	else
		return (0);
	if (!*newargv)
		return (1);
	return (0);
}
