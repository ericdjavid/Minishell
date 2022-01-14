/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:42:20 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 10:51:30 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_failed2(int **fds, char **newargv, int *ret)
{
	ft_close_fd(fds[1][1]);
	free_mati(fds, 2);
	free_matc(newargv);
	if (ret)
		free(ret);
	if (g_status == 42)
		return (-1);
	return (1);
}

void	free_in_builtins(int **fds, int *ret, char **newargv)
{
	free_mati(fds, 2);
	free(ret);
	free_matc(newargv);
}

int	exec_builtins(char **newargv, t_control *list, char **paths)
{
	int	*ret;
	int	**fds;
	int	exec;

	fds = init_fds(1);
	if (!fds)
		return (-1);
	fds[0][0]++;
	ret = ft_manage_fds(&newargv, paths, fds, 0);
	if (!ret)
	{
		return (malloc_failed2(fds, newargv, ret));
	}
	else
	{
		if (ret[1] == 0)
			ret[1] = 1;
		exec = ft_builtins(newargv, list, ret[1]);
		ft_close_fd(fds[1][1]);
		if (ret[1] != 1)
			ft_close_fd(ret[1]);
	}
	free_in_builtins(fds, ret, newargv);
	return (exec);
}

int	ft_builtins(char **newargv, t_control *list, int fd)
{
	size_t	len_0;

	if (!newargv[0])
		return (0);
	len_0 = ft_strlen(newargv[0]);
	if (!ft_strncmp(newargv[0], "echo", len_0))
		return (ft_echo(newargv, fd));
	else if (!ft_strncmp(newargv[0], "pwd", len_0))
		return (ft_pwd(fd));
	else if (!ft_strncmp(newargv[0], "cd", len_0))
		return (ft_cd(newargv, list));
	else if (!ft_strncmp(newargv[0], "export", len_0))
		return (ft_export(list, newargv));
	else if (!ft_strncmp(newargv[0], "env", len_0))
		return (ft_env(list));
	else if (!ft_strncmp(newargv[0], "exit", len_0))
		return (ft_exit(newargv));
	else if (!ft_strncmp(newargv[0], "unset", len_0))
		return (ft_unset(list, newargv));
	if (!ft_strncmp(newargv[0], "/usr/bin/clear", len_0))
		return (ft_clear(newargv));
	return (-1);
}

int	is_builtins(char *newargv)
{
	size_t	len;

	len = ft_strlen(newargv);
	if (!ft_strncmp(newargv, "echo", len))
		return (1);
	else if (!ft_strncmp(newargv, "pwd", len))
		return (1);
	else if (!ft_strncmp(newargv, "cd", len))
		return (1);
	else if (!ft_strncmp(newargv, "export", len))
		return (1);
	else if (!ft_strncmp(newargv, "env", len))
		return (1);
	else if (!ft_strncmp(newargv, "unset", len))
		return (1);
	else if (!ft_strncmp(newargv, "exit", len))
		return (1);
	return (0);
}
