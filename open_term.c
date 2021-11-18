/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:01:20 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 08:08:44 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_term(void)
{
	char	**xterm;
	pid_t	child_pid;

	xterm = init_xterm();
	if (!xterm)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
	{
		free_matc(xterm);
		return (0);
	}
	if (child_pid == 0)
	{
		if (execve(xterm[0], xterm, NULL) == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

char	**init_xterm(void)
{
	char	**xterm;

	xterm = malloc(sizeof(char *) * 4);
	if (!xterm)
		return (0);
	xterm[0] = ft_strdup("/usr/bin/xterm");
	if (!xterm[0])
	{
		free_matc(xterm);
		return (0);
	}
	xterm[1] = ft_strdup("-e");
	if (!xterm[1])
	{
		free_matc(xterm);
		return (0);
	}
	xterm[2] = ft_strdup("minishell");
	if (!xterm[2])
	{
		free_matc(xterm);
		return (0);
	}
	xterm[3] = 0;
	return (xterm);
}
