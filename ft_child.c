/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/24 15:18:51 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_child(char ***newargv, int n_newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;

	ret = init_ret();
	if (!ret)
		return (0);
	ret = ft_manage_fds(newargv, n_newargv, paths, fds);
	if (!ret)
		exit(status);
	else if (ft_builtins(newargv[n_newargv], list));
	else if (access(newargv[n_newargv][0], X_OK))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
				newargv[n_newargv][0]);
		status = 127;
	}
	else if (execve(newargv[n_newargv][0],
				newargv[n_newargv], NULL) < 0)
		status = 1;
	exit(status);
	return (0);
}
