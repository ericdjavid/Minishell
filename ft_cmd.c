/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 10:57:42 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(int **fds, pid_t *child_pid, int n_fds)
{
	if (fds)
		free_mati(fds, n_fds);
	if (child_pid)
		free(child_pid);
	return (0);
}

void	wait_cmds_free(int n_pid, pid_t *child_pid, int **fds)
{
	int	c;

	c = 0;
	while (c < n_pid - 1)
	{
		waitpid(child_pid[c], &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		if (g_status == 131)
			write(1, "\n", 1);
		if (g_status == 42)
			ft_printf_fd(2, RED "minishell: error with a malloc\n" END);
		c++;
	}
	free_mati(fds, n_pid + 1);
	free(child_pid);
}

void	close_fds_in_parent(int **fds, int config)
{
	if (config == 1)
	{
		if (fds[0][0] > 2)
			ft_close_fd(fds[fds[0][0] - 2][0]);
		ft_close_fd(fds[fds[0][0]][1]);
	}
	else
	{
		ft_close_fd(fds[fds[0][0]][0]);
		if (fds[0][0] > 1)
			ft_close_fd(fds[fds[0][0] - 1][0]);
	}
}

int	ft_cmd(char ***newargv, char **paths, t_control *list, int n_pid)
{
	int		n_newargv;
	int		**fds;
	pid_t	*child_pid;

	n_newargv = 0;
	child_pid = malloc(sizeof(pid_t) * n_pid);
	fds = init_fds(n_pid);
	if (!fds || !child_pid)
		return (exit_cmd(fds, child_pid, n_pid + 1));
	while (newargv[++n_newargv])
	{
		fds[0][0] += 1;
		child_pid[n_newargv - 1] = fork();
		if (child_pid[n_newargv - 1] == -1)
			return (0);
		else if (child_pid[n_newargv - 1] == 0
			&& !(ft_child(&newargv[n_newargv], paths, list, fds)))
			return (g_status);
		check_heredoc(child_pid[n_newargv - 1], newargv[n_newargv]);
		close_fds_in_parent(fds, 1);
	}
	close_fds_in_parent(fds, 0);
	wait_cmds_free(n_pid, child_pid, fds);
	return (g_status);
}

int	**init_fds(int n_cmd)
{
	int	**fds;
	int	c;

	fds = malloc(sizeof(int *) * (n_cmd + 2));
	if (!fds)
		return (0);
	c = 0;
	fds[c] = malloc(sizeof(int));
	if (!fds[c])
		return (0);
	fds[c++][0] = 0;
	if (n_cmd == 1)
		n_cmd++;
	while (c < n_cmd)
	{
		fds[c] = malloc(sizeof(int) * 2);
		if (!fds[c] || pipe(fds[c]) == -1)
		{
			free_mati(fds, c);
			return (0);
		}
		c++;
	}
	fds[c] = 0;
	return (fds);
}
