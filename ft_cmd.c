/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/11/22 16:06:29 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(char ***newargv, char **paths, t_control *list)
{
	pid_t	child_pid;
	int		n_newargv;
	int		**fds;
	int		*ret;

	n_newargv = 0;
	fds = init_fds();
	if (!fds)
		return (0);
	ret = init_ret();
	if (!ret)
	{
		free_mati(fds, 2);
		return (0);
	}
	while (newargv[n_newargv])
	{
		if (pipe(fds[0]) == -1)
			return (0);
		child_pid = fork();
		if (child_pid == -1)
			return (0);
		if (child_pid == 0)
		{
			ret = ft_manage_fds(newargv, n_newargv, paths, fds);
			if (!ret)
				exit(status);
			else if (ft_builtins(newargv[n_newargv], list))
				exit(status);
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
		}
		else
		{
			ft_close_fd(fds[0][1]);
			while (wait(&status) > 0);
			if (status == 512)
				status = 258;
			else
				status = WEXITSTATUS(status);
			fds[1][0] = fds[0][0];
		}
		n_newargv++;
	}
	return (1);
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
