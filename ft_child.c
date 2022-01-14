/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 11:45:03 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(pid_t child_pid, char **str)
{
	int	status;
	int	i;

	i = -1;
	if (child_pid > 0)
	{
		while (str[++i])
		{
			if (!ft_strncmp(str[i], "<<", ft_strlen("<<")))
				wait(&status);
		}
	}
	return ;
}

int	ft_child(char ***newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;
	char	**new_env;
	int		builtins;

	builtins = 0;
	new_env = ft_get_envs_var(list);
	signal(SIGQUIT, SIG_DFL);
	ret = ft_manage_fds(newargv, paths, fds, 1);
	if (!ret)
		return (close_fds_in_child(fds, builtins, newargv - 1, ret));
	else if (ft_builtins(*newargv, list, 1) > -1)
		builtins = 1;
	else if (!ft_strchr((*newargv)[0], '/') || access((*newargv)[0], F_OK))
		is_directory((*newargv)[0]);
	else if (access((*newargv)[0], X_OK))
	{
		ft_printf_fd(2, "minishell: permission non accordée: %s\n",
			(*newargv)[0]);
		g_status = 126;
	}
	else if (execve((*newargv)[0],
		(*newargv), new_env) < 0)
		g_status = 1;
	free_in_child(new_env);
	return (close_fds_in_child(fds, builtins, newargv - 1, ret));
}

void	is_directory(char *arg)
{
	DIR	*fdir;

	if (ft_strchr(arg, '/'))
	{
		fdir = opendir(arg);
		if (!fdir)
		{
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
				(arg));
		}
		else
		{
			ft_printf_fd(2, "minishell: %s: Is a directory\n",
				(arg));
			closedir(fdir);
		}
	}
	else
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
			(arg));
	}
	g_status = 127;
}
