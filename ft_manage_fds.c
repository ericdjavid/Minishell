/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:59:11 by abrun             #+#    #+#             */
/*   Updated: 2021/11/21 21:13:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_manage_fds(char ***newargv, int n_n, char **paths, int *fds, int fd_save)
{
	int	*ret;

	ret = malloc(sizeof(int) * 2);
	if (!ret)
		return (0);
	ret[0] = ft_read_input(newargv, n_n, paths);
	ret[1] = ft_redirection(newargv, n_n);
	newargv[n_n][0] = init_cmd_path(newargv[n_n][0], paths);
	if (!ret[0] || !ret[1])
		exit (1);
	else if (ret[0] == 1 && ret[1] != 2 && ret[1] != 5
			&& (ft_matlen(newargv[n_n]) > 1
				|| n_n > 0))
	{
		ft_dup2(fd_save, STDIN_FILENO);
		ft_close_fd(fd_save);
	}
	if (ret[1] != 3 && ret[1] != 5 && newargv[n_n + 1])
		ft_dup2(fds[1], STDOUT_FILENO);
	ft_close_fd(fds[0]);
	return (ret);
}
