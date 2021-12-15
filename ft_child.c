/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 17:48:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_child(char ***newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;

	signal(SIGQUIT, SIG_DFL);
	ret = ft_manage_fds(newargv, paths, fds);
	if (!ret)
		exit(status);
	else if (ft_builtins(*newargv, list))
		;
	else if (access((*newargv)[0], F_OK))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
			(*newargv)[0]);
		status = 127;
	}
	else if (access((*newargv)[0], X_OK))
	{
		ft_printf_fd(2, "minishell: permission non accordée: %s\n",
			(*newargv)[0]);
		status = 126;
	}
	else if (execve((*newargv)[0],
		(*newargv), NULL) < 0)
		status = 1;
	free(ret);
	exit(status);
}
