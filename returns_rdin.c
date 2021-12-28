/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns_rdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:34:29 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 15:19:32 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_readin(char ***files, char **heredoc, int last)
{
	int	fdin;
	int	c;

	c = 0;
	while ((*files)[c])
	{
		fdin = get_outfd((*files)[c], 2);
		if (fdin < 0)
			return (exit_readin(*files, *heredoc));
		c++;
	}
	return (dup_readin_2(heredoc, files, last, fdin));
}

int	dup_readin_2(char **heredoc, char ***files, int last, int fdin)
{
	int	fds[2];

	if (*heredoc && last == 1)
	{
		if (pipe(fds) == -1)
			return (exit_readin(*files, *heredoc));
		write(fds[1], *heredoc, ft_strlen(*heredoc));
		ft_dup2(fds[0], STDIN_FILENO);
		ft_close_fd(fds[0]);
		ft_close_fd(fds[1]);
		return (2);
	}
	else if (last == 2)
	{
		ft_dup2(fdin, STDIN_FILENO);
		ft_close_fd(fdin);
		return (2);
	}
	free_matc(*files);
	free(*heredoc);
	return (1);
}

int	exit_readin(char **files, char *heredoc)
{
	free_matc(files);
	if (heredoc)
		free(heredoc);
	return (0);
}
