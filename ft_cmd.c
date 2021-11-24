/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/11/24 15:18:50 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(char ***newargv, char **paths, t_control *list)
{
	int		n_newargv;
	int		**fds;
	pid_t	child_pid;

	n_newargv = 0;
	fds = init_fds();
	if (!fds)
		return (0);
	while (newargv[n_newargv])
	{
		if (pipe(fds[0]) == -1)
			return (0);
		child_pid = fork();
		if (child_pid == -1)
			return (0);
		if (child_pid == 0)
			if (!(ft_child(newargv, n_newargv, paths, list, fds)))
				return (status_free(fds));
		ft_close_fd(fds[0][1]);
		while (wait(&status) > 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		fds[1][0] = fds[0][0];
		n_newargv++;
	}
	return (status_free(fds));
}

int	*init_ret(void)
{
	int	*ret;

	ret = malloc(sizeof(int) * 2);
	if (!ret)
		return (0);
	ret[0] = 1;
	ret[1] = 1;
	return (ret);
}

int	**init_fds(void)
{
	int	**fds;

	fds = malloc(sizeof(int *) * 2);
	if (!fds)
		return (0);
	fds[0] = malloc(sizeof(int) * 2);
	if (!fds[0])
	{
		free(fds);
		return (0);
	}
	fds[1] = malloc(sizeof(int));
	if (!fds[1])
	{
		free(fds[0]);
		free(fds);
		return (0);
	}
	fds[1][0] = 0;
	return (fds);
}

int	status_free(int **fds)
{
	free_mati(fds, 2);
	return (status);
}

int	get_n_cmd(char *cmd_line)
{
	int	n_cmd;
	int	c;

	n_cmd = 1;
	c = 0;
	while (cmd_line[c])
	{
		if (cmd_line[c] == '|')
			n_cmd++;
		c++;
	}
	return (n_cmd);
}
