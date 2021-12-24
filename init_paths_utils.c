/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:03:52 by abrun             #+#    #+#             */
/*   Updated: 2021/12/24 17:05:58 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_cmd_path(char *cmd, char **paths)
{
	int		n_path;
	size_t	cmd_len;
	char	*cmd_path;

	if (is_builtins(cmd) || *cmd == '/')
		return (cmd);
	n_path = 0;
	cmd_len = ft_strlen(cmd);
	while (paths[n_path])
	{
		cmd_path = malloc(ft_strlen(paths[n_path]) + cmd_len + 1);
		ft_strcpy(cmd_path, paths[n_path]);
		ft_strcat(cmd_path, cmd);
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
