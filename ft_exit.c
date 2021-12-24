/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:14:10 by abrun             #+#    #+#             */
/*   Updated: 2021/12/24 15:12:58 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **arg)
{
	int	arglen;

	write(1, "exit\n", 5);
	arglen = ft_matlen(arg);
	if (arglen == 1)
		return (0);
	else if (arglen == 2)
	{
		if (ft_str_is_num(arg[1]))
			g_status = ft_atoi(arg[1]);
		else
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				arg[1]);
			g_status = 2;
		}
	}
	else
		return (ft_exit_2(arg));
	return (0);
}

int	ft_exit_2(char **arg)
{
	if (ft_str_is_num(arg[1]))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		if (!g_status)
			g_status = 1;
		return (g_status);
	}
	else
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			arg[1]);
		g_status = 2;
	}
	return (0);
}
