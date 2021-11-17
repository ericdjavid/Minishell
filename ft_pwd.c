/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:32:46 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 17:36:24 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **newargv)
{
	char	buf[1024];

	if (ft_matlen(newargv) != 1)
		return (0);
	ft_printf_fd(1, "%s\n", getcwd(buf, 1024));
	return (1);
}
