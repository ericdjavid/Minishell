/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:32:46 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 16:36:59 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **newargv)
{
	char	buf[1024];
	char	*ret;

	if (ft_matlen(newargv) != 1)
		return (0);
	else
		ret = getcwd(buf, 1024);
	if (!ret)
	{
		write(2, "pwd: error retrieving current directory: getcwd: can", 52);
		write(2, "not access parent directories:", 30);
		write(2, " No such file or directory\n", 27);
		g_status = 1;
	}
	else
		ft_printf_fd(1, "%s\n", ret);
	return (1);
}
