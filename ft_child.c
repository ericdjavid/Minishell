/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 16:38:37 by abrun            ###   ########.fr       */
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

int	ft_child(char ***newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;
	char	**new_env;

	new_env = ft_get_envs_var(list);
	signal(SIGQUIT, SIG_DFL);
	ret = ft_manage_fds(newargv, paths, fds);
	if (!ret)
		exit(g_status);
	else if (ft_builtins(*newargv, list) > -1)
		;
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
	if (new_env)
		free_matc(new_env);
	free(ret);
	exit(g_status);
}
