/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:59:11 by abrun             #+#    #+#             */
/*   Updated: 2021/12/24 18:16:22 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_manage_fds(char ***newargv, char **paths, int **fds)
{
	int	*ret;

	ret = init_ret();
	if (!ret)
		return (0);
	ft_close_fds(fds, fds[0][0]);
	ret[0] = ft_read_input(newargv, paths);
	ret[1] = ft_redirection(newargv);
	(*newargv)[0] = init_cmd_path((*newargv)[0], paths);
	if (!ret[0] || !ret[1])
	{
		free(ret);
		return (0);
	}
	else if (check_ret_stdin(ret)
			&& ((ft_matlen((*newargv)) > 1) || *(newargv - 1))
			&& fds[0][0] > 1)
	{
		ft_dup2(fds[fds[0][0] - 1][0], STDIN_FILENO);
		ft_close_fd(fds[fds[0][0] - 1][0]);
	}
	if (check_ret_stdout(ret) && *(newargv + 1))
		ft_dup2(fds[fds[0][0]][1], STDOUT_FILENO);
	return (ret);
}

int	check_ret_stdin(int *ret)
{
	if (ret[0] == 1 && ret[1] != 2 && ret[1] != 5
			&& ret[1] != 9 && ret[1] != 6)
		return (1);
	return (0);
}

int	check_ret_stdout(int *ret)
{
	if (ret[1] != 3 && ret[1] != 5
			&& ret[1] != 9 && ret[1] != 6)
		return (1);
	return (0);
}
