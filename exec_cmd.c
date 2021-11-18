/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:10:52 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 10:40:02 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths)
{
	char	**newargv;
	int		ret;

	ret = 0;
	newargv = ft_split(cmd_line, 32);
	if (!newargv)
		return (0);
	if(ft_pipe(cmd_line, paths) > 0)
	{
		ret = 0;
	} 
	else if (ft_builtins(newargv))
	{
		ret = 0;
	}
	else
	{
		newargv[0] = init_cmd_path(newargv[0], paths);
		ret = ft_non_builtins(newargv);
	}
	free_matc(newargv);
	return (ret);
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

int	ft_non_builtins(char **newargv)
{
	pid_t	child_pid;
	int		fds[2];
	int		ret;
	
	ret = 0;
	if (pipe(fds) == -1)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (access(newargv[0], X_OK))
		{
			ft_printf_fd(2, "minishell: %s: command not found\n", newargv[0]);
			ret = 127;
		}
		else if (execve(newargv[0], newargv, NULL) == -1)
			ret = 1;
	}
	else
		while ((wait(NULL)) > 0);
	return (ret);
}
