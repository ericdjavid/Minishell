/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:59:11 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 11:45:00 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*exit_manage_free(int *ret, int config, int forked)
{
	if (config)
	{
		if (ret[1] == -1 || ret[0] == -1 || config == 2)
			g_status = 42;
		else
			g_status = 2;
	}
	if (config == 666)
		g_status = 0;
	else
		g_status = 42;
	if (!forked)
		return (ret);
	free(ret);
	return (0);
}

int	*ft_manage_fds(char ***newargv, char **paths, int **fds, int forked)
{
	int	*ret;

	ft_close_fds(fds, fds[0][0]);
	ret = ft_manage_rdwr(newargv, forked);
	if (!ret)
		return (0);
	if ((*newargv)[0])
	{
		(*newargv)[0] = init_cmd_path((*newargv)[0], paths);
		if (!(*newargv)[0])
			return (exit_manage_free(ret, 2, forked));
	}
	if (!ret[0] && ((ft_matlen((*newargv)) > 1) || *(newargv - 1))
		&& fds[0][0] > 1)
	{
		ft_dup2(fds[fds[0][0] - 1][0], STDIN_FILENO);
		ft_close_fd(fds[fds[0][0] - 1][0]);
	}
	if (!ret[1] && (forked && *(newargv + 1)))
		ft_dup2(fds[fds[0][0]][1], STDOUT_FILENO);
	return (ret);
}
