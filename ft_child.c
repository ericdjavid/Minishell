/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2022/01/13 14:46:37 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_env(t_element *tmp)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(tmp->str) + 1));
	if (!str)
		return (NULL);
	while (tmp->str[i])
	{
		str[i] = tmp->str[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_add_from_list(char **neo_env, t_element *first, int i)
{
	t_element	*tmp;

	tmp = first;
	if (!tmp)
		return (FAILURE);
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		neo_env[i] = ft_fill_env(tmp);
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_get_envs_var(t_control *list)
{
	char		**neo_env;
	t_element	*tmp;
	int			i;

	i = 0;
	neo_env = malloc(sizeof(char *) * (list->size + 1));
	if (!neo_env)
		return (0);
	i = ft_add_from_list(neo_env, list->first_env, i);
	tmp = list->first_env_var;
	while (tmp && tmp->str)
	{
		neo_env[i] = ft_strdup(tmp->str);
		i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	neo_env[i] = 0;
	return (neo_env);
}

int	close_fds_in_child(int **fds, int builtins, char ***prev)
{
	int	n;

	if (builtins)
	{
		n = fds[0][0];
		ft_close_fd(1);
		if (prev)
			ft_close_fd(0);
		ft_close_fd(fds[n][1]);
		n++;
		while (fds[n])
		{
			ft_close_fd(fds[n][1]);
			n++;
		}
		if (fds[0][0] > 2)
			ft_close_fd(fds[fds[0][0] - 2][0]);
	}
	else
	{
		n = fds[0][0];
		ft_close_fd(fds[n][1]);
		while (fds[++n])
			ft_close_fd(fds[n][1]);
		n = fds[0][0] - 1;
	}
	exit(g_status);
}

int	ft_child(char ***newargv, char **paths, t_control *list, int **fds, int hd_pid)
{
	int		*ret;
	char	**new_env;
	int		builtins;

	builtins = 0;
	new_env = ft_get_envs_var(list);
	signal(SIGQUIT, SIG_DFL);
	printf(PINK"child with pid - %d\n"END, hd_pid);
	ret = ft_manage_fds(newargv, paths, fds, 1);
	if (!ret)
		return (close_fds_in_child(fds, builtins, newargv - 1));
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
	free_in_child(new_env, ret);
	return (close_fds_in_child(fds, builtins, newargv - 1));
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
