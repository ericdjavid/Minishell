/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:32:52 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 18:33:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_outfd(char *file, int config)
{
	int	outfd;

	outfd = -1;
	if (!file)
	{
		ft_printf_fd(2, "minishell: syntax error\n");
		g_status = 2;
		return (-2);
	}
	else if (!access(file, F_OK))
	{
		outfd = get_outfd_2(file, config);
	}
	else if (config != 1)
	{
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	}
	else
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			file);
	}
	return (outfd);
}

int	get_outfd_2(char *file, int config)
{
	int	outfd;

	outfd = -1;
	if (config == 3 && !access(file, W_OK))
		outfd = open(file, O_TRUNC | O_WRONLY);
	else if (config == 4 && !access(file, W_OK))
		outfd = open(file, O_WRONLY | O_APPEND);
	else if (config == 2 && !access(file, R_OK))
		outfd = open(file, O_RDONLY);
	else
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
		g_status = 1;
	}
	return (outfd);
}
