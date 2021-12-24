/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:36:14 by abrun             #+#    #+#             */
/*   Updated: 2021/12/24 15:38:18 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clear(char **newargv)
{
	int	ret;

	ret = is_option_of_clear(newargv);
	if (ft_matlen(newargv) > 1 && !ret)
	{
		ft_printf_fd(2, "Usage: clear [options]\n\nOptions:\n");
		ft_printf_fd(2, "-T TERM    use this instead of $TERM\n");
		ft_printf_fd(2, "-V         print curses-version\n");
		ft_printf_fd(2, "-x         do not try to clear scrollback\n");
		g_status = 1;
	}
	else if (ret == 1)
	{
		write(1, "\E[H\E[2J", 7);
		g_status = 0;
	}
	else
		return (0);
	return (1);
}

int	is_option_of_clear(char **newargv)
{
	size_t	len;

	len = ft_strlen(newargv[1]);
	if (!ft_strncmp(newargv[1], "-T", len))
		return (1);
	else if (!ft_strncmp(newargv[1], "-V", len))
	{
		return (2);
	}
	else if (!ft_strncmp(newargv[1], "-x", len) && ft_matlen(newargv) == 2)
	{
		return (1);
	}
	return (0);
}
