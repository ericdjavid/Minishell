/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:32:07 by abrun             #+#    #+#             */
/*   Updated: 2021/12/28 14:09:58 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_paths(char **envp)
{
	int		c;
	int		c_2;
	char	**paths;

	c = 0;
	while (envp[c] && ft_strncmp(envp[c], "PATH", 4))
		c++;
	if (!envp[c])
		return (0);
	c_2 = 0;
	while (envp[c][c_2] && envp[c][c_2] != '/')
		c_2++;
	paths = fill_paths(envp[c], c_2);
	return (paths);
}

char	**fill_paths(char *envp, int count)
{
	char	**paths;
	int		n_path;
	int		path_len;

	n_path = 0;
	path_len = get_path_len(envp, count);
	paths = malloc(sizeof(char *) * (path_len + 1));
	if (!paths)
		return (0);
	while (envp[count])
	{
		paths[n_path] = ft_add_one_path(envp, &count);
		if (!paths[n_path])
		{
			free_matc(paths);
			return (0);
		}
		n_path++;
	}
	paths[n_path] = 0;
	return (paths);
}

int	get_path_len(char *envp, int count)
{
	int	len;

	len = 0;
	while (envp[count])
	{
		if (envp[count] == ':')
			len++;
		count++;
	}
	if (len)
		len++;
	return (len);
}

char	*ft_add_one_path(char *envp, int *count)
{
	char	*path;
	int		n;
	int		path_len;

	path = init_param_path(envp, *count, &path_len, &n);
	if (!path)
		return (0);
	while (path_len-- && envp[*count])
	{
		if (envp[*count] != 32)
		{
			path[n] = envp[*count];
			n++;
		}
		*count += 1;
	}
	if (path[n - 1] != '/')
		path[n++] = '/';
	path[n] = 0;
	if (envp[*count])
		*count += 1;
	return (path);
}

char	*init_param_path(char *envp, int count, int *path_len, int *n)
{
	char	*path;

	*path_len = 0;
	while (envp[count + *path_len] && envp[count + *path_len] != ':')
		*path_len += 1;
	path = malloc(*path_len + 2);
	if (!path)
		return (0);
	*n = 0;
	return (path);
}
