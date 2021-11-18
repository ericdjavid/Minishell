/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 10:49:27 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(char *cmd_line, char **paths)
{
	char	***newargv;
	int		ret;

	if (!ft_strchr(cmd_line, '|'))
		return (0);
	newargv = init_newargv(cmd_line, paths);
	if (!newargv)
		return (-1);
	ret = ft_cmd_n(newargv);
	if (!ret)
		return (-1);
	return (ret);
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

int	ft_cmd_n(char ***newargv)
{
	pid_t	child_pid;
	int		n_newargv;
	int		ret;
	int		fd_save;
	int		fds[2];

	ret = 1;
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
			if (newargv[n_newargv + 1])
				ft_dup2(fds[1], STDOUT_FILENO);
			ft_dup2(fd_save, STDIN_FILENO);
			ft_close_fd(fd_save);
			ft_close_fd(fds[0]);
			if (access(newargv[n_newargv][0], X_OK))
			{
				ft_printf_fd(2, "minishell: %s: command not found\n",
						newargv[n_newargv][0]);
				ret = 127;
			}
			else if (execve(newargv[n_newargv][0], newargv[n_newargv],
						NULL) == -1)
				ret = 1;
		}
		else
		{
			ft_close_fd(fds[1]);
			while (wait(NULL) > 0);
			fd_save = fds[0];
		}
		n_newargv++;
	}
	return(ret);
}
