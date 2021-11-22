/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:59:11 by abrun             #+#    #+#             */
/*   Updated: 2021/11/22 13:19:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_manage_fds(char ***newargv, int n_n, char **paths, int **fds)
{
	int	*ret;

	ret = init_ret();
	if (!ret)
		return (0);
	ret[0] = ft_read_input(newargv, n_n, paths);
	ret[1] = ft_redirection(newargv, n_n);
	ft_printf_fd(2, "ret_0 : %d | ret_1 : %d\n", ret[0], ret[1]);
	newargv[n_n][0] = init_cmd_path(newargv[n_n][0], paths);
	if (!ret[0] || !ret[1])
		return (0);
	else if (check_ret_stdin(ret)
			&& (ft_matlen(newargv[n_n]) > 1 || n_n > 0))
	{
		ft_dup2(fds[1][0], STDIN_FILENO);
		ft_close_fd(fds[1][0]);
	}
	if (check_ret_stdout(ret) && newargv[n_n + 1])
		ft_dup2(fds[0][1], STDOUT_FILENO);
	ft_close_fd(fds[0][0]);
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
