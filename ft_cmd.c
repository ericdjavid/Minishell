/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/11/19 21:21:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(char ***newargv, char **paths)
{
	pid_t	child_pid;
	int		n_newargv;
	int		fd_save;
	int		fds[2];
	int		ret[2];

	(void)paths;
	ret[0] = 1;
	ret[1] = 1;
	n_newargv = 0;
	fd_save = 0;
	while (newargv[n_newargv])
	{
		if (pipe(fds) == -1)
			return (0);
		child_pid = fork();
		if (child_pid == -1)
			return (0);
		if (child_pid == 0)
		{
			ret[0] = ft_read_input(newargv, n_newargv, paths);
			ret[1] = ft_redirection(newargv, n_newargv);
			if (!ret[0] || !ret[1])
				return (0);
			else if (ret[0] == 1 && ret[1] != 2
					&& (ft_matlen(newargv[n_newargv]) > 1
					|| n_newargv > 0))
			{
				ft_dup2(fd_save, STDIN_FILENO);
				ft_close_fd(fd_save);
			}
			if (ret[1] != 3 && newargv[n_newargv + 1])
				ft_dup2(fds[1], STDOUT_FILENO);
			ft_close_fd(fds[0]);
			if (ret[1] > 0 && ft_builtins(newargv[n_newargv]))
			{
				ret[1] = 1;
				exit(1);
			}
			else if (ret[1] > 0 && access(newargv[n_newargv][0], X_OK))
			{
				ft_printf_fd(2, "minishell: %s: command not found\n",
						newargv[n_newargv][0]);
				ret[1] = 127;
				exit(127);
			}
			else if (ret[1] > 0 && execve(newargv[n_newargv][0],
				newargv[n_newargv], NULL) == -1)
				ret[1] = 1;
			exit(ret[1]);
		}
		else
		{
			ft_close_fd(fds[1]);
			while (wait(NULL) > 0);
			fd_save = fds[0];
		}
		n_newargv++;
	}
	return(ret[1]);
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
