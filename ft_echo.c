/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:38:14 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 16:09:18 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **newargv, int fd)
{
	char	c;

	c = 0;
	if (ft_matlen(newargv) == 1)
	{
		write(fd, "\n", 1);
		return (1);
	}
	else if (!ft_strncmp(newargv[1], "-n", 2))
	{
		while (newargv[1 + c] && check_echo_arg(newargv[1 + c]))
			c++;
		write_newargv(newargv, 1 + c, fd);
	}
	else
	{
		write_newargv(newargv, 1, fd);
	}
	g_status = 0;
	return (1);
}

void	write_newargv(char **newargv, int c, int fd)
{
	int	ret;

	ret = c;
	while (newargv[c])
	{
		if (!ft_strncmp(newargv[c], "$?", ft_strlen(newargv[c])))
			ft_putnbr_fd(g_status, fd);
		else
			write(fd, newargv[c], ft_strlen(newargv[c]));
		c++;
		if (newargv[c])
			write(fd, " ", 1);
	}
	if (ret == 1)
		write(fd, "\n", 1);
}

int	check_echo_arg(char *newargv)
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
