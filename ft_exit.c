/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:14:10 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 16:46:28 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **arg)
{
	int	arglen;

	ft_printf_fd(1, "exit\n"); 
	arglen = ft_matlen(arg);
	if (arglen == 1)
		return (0);
	else if (arglen == 2)
	{
		if (ft_strIsNum(arg[1]))
			status = ft_atoi(arg[1]);
		else
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				arg[1]);
	}
	else
	{
		if (ft_strIsNum(arg[1]))
			write(2, "minishell: exit: too many arguments\n", 35); 
		else
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				arg[1]);
	}
	return (0);
}
