/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:03:52 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 16:02:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_cmd_path(char *cmd, char **paths)
{
	int		n_path;
	size_t	cmd_len;
	char	*cmd_path;

	if (cmd == NULL)
		return (0);
	if (is_builtins(cmd) || ft_strchr(cmd, '/') || !*cmd)
		return (cmd);
	n_path = 0;
	cmd_len = ft_strlen(cmd);
	while (paths && paths[n_path])
	{
		cmd_path = init_cmd_with_path(cmd, paths[n_path], cmd_len);
		if (!cmd_path)
			return (0);
		if (!access(cmd_path, F_OK))
		{
			free(cmd);
			return (cmd_path);
		}
		n_path++;
		free(cmd_path);
	}
	return (cmd);
}

char	*init_cmd_with_path(char *cmd, char *path, size_t cmd_len)
{
	char	*cmd_path;

	cmd_path = malloc(ft_strlen(path) + cmd_len + 1);
	if (!cmd_path)
	{
		free(cmd);
		return (0);
	}
	ft_strcpy(cmd_path, path);
	ft_strcat(cmd_path, cmd);
	return (cmd_path);
}
