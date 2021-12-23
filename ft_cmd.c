/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/12/23 12:10:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(char ***newargv, char **paths, t_control *list)
{
	int		n_newargv;
	int		**fds;
	pid_t	child_pid[n_pid(newargv)];
	int		c;

	n_newargv = 1;
	fds = init_fds(newargv);
	if (!fds)
		return (0);
	while (newargv[n_newargv])
	{
		fds[0][0] += 1;
		if (!ft_strncmp(newargv[n_newargv][0], "export",
					ft_strlen(newargv[n_newargv][0]))
				&& newargv[n_newargv][1])
			ft_get_new_var(list, newargv[n_newargv]);
		if (!ft_strncmp(newargv[n_newargv][0], "unset",
					ft_strlen(newargv[n_newargv][0]))
				&& newargv[n_newargv][1])
			ft_unset(list, newargv[n_newargv]);
		child_pid[n_newargv - 1] = fork();
		if (child_pid[n_newargv - 1] == -1)
			return (0);
		else if (child_pid[n_newargv - 1] == 0)
		{
			if (!(ft_child(&newargv[n_newargv], paths, list, fds)))
				return (status_free(fds));
		}
		else
		{
			if (fds[0][0] > 2)
				ft_close_fd(fds[fds[0][0] - 2][0]);
			ft_close_fd(fds[fds[0][0]][1]);
		}
		n_newargv++;
	}
	c = 0;
	while (c < n_newargv - 1)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 131)
			write(1, "\n", 1);
		c++;
	}
	free_mati(fds, n_newargv);
	return (status);
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

int	**init_fds(char ***newargv)
{
	int	**fds;
	int	n_cmd;
	int	c;

	n_cmd = 1;
	while (newargv[n_cmd + 1])
		n_cmd++;
	fds = malloc(sizeof(int *) * (n_cmd + 2));
	if (!fds)
		return (0);
	c = 0;
	fds[c] = malloc(sizeof(int));
	if (!fds[c])
		return (0);
	fds[c][0] = 0;
	c++;
	while (c < n_cmd + 1)
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

int	n_pid(char ***newargv)
{
	int	c;

	c = 1;
	while (newargv[c])
		c++;
	return (c);
}
