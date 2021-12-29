/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:56:30 by abrun             #+#    #+#             */
/*   Updated: 2021/12/28 15:32:07 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(int **fds, int n)
{
	if (n == 1)
	{
		ft_close_fds_around(fds, n);
		ft_close_fd(fds[1][0]);
	}
	else
	{
		ft_close_fd(fds[n][0]);
		ft_close_fds_around(fds, n);
	}
}

void	ft_close_fds_around(int **fds, int n)
{
	n++;
	while (fds[n])
	{
		ft_close_fd(fds[n][0]);
		n++;
	}
}
