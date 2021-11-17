/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:10:52 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 14:03:26 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths)
{
	pid_t	child_pid;
	int		fds[2];
	char	**newargv;

	if (pipe(fds) == -1)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	newargv = ft_split(cmd_line, 32);
	newargv[0] = init_cmd_path(newargv[0], paths);
	if (child_pid == 0)
	{
		if (execve(newargv[0], newargv, NULL) == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
	free_matc(newargv);
	return (1);
}

char	*init_cmd_path(char *cmd, char **paths)
{
	int		n_path;
	size_t	cmd_len;
	char	*cmd_path;

	n_path = 0;
	cmd_len = ft_strlen(cmd);
	while (paths[n_path])
	{
		cmd_path = malloc(ft_strlen(paths[n_path]) + cmd_len + 1);
		ft_strcpy(cmd_path, paths[n_path]);
		ft_strcat(cmd_path, cmd);
		if (!access(cmd_path, X_OK))
		{
			free(cmd);
			return (cmd_path);
		}
		n_path++;
		free(cmd_path);
	}
	return (cmd);
}
