/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:24:21 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 09:25:17 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}

void	ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}
