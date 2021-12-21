/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:14:10 by abrun             #+#    #+#             */
/*   Updated: 2021/12/21 16:18:02 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **arg)
{
	int	arglen;

	arglen = ft_matlen(arg);
	if (arglen == 1)
	{
		printf("yesss\n");
		free_matc(arg);
		return (1);
	}
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
	// free_matc(arg);
	return (1);
}
