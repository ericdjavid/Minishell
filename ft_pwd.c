/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:32:46 by abrun             #+#    #+#             */
/*   Updated: 2021/12/23 18:29:30 by abrun            ###   ########.fr       */
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
		write(2, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 110);
		status = 1;
	}
	else
		ft_printf_fd(1, "%s\n", ret);
	return (1);
}
