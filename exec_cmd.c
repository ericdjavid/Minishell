/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:10:52 by abrun             #+#    #+#             */
/*   Updated: 2021/11/28 16:34:55 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths, t_control *list)
{
	char	***newargv;

	if (!cmd_line || !ft_strncmp(cmd_line, "exit", ft_strlen(cmd_line)))
		return (0);
	newargv = init_newargv(cmd_line, paths);
	if (!newargv)
		return (-1);
	ft_cmd(newargv, paths, list);
	free_newargv(newargv);
	return (1);
}

char	*init_cmd_path(char *cmd, char **paths)
{
	int		n_path;
	size_t	cmd_len;
	char	*cmd_path;

	if (is_builtins(cmd))
		return (cmd);
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

void	free_newargv(char ***matc)
{
	int	n;

	n = 1;
	while (matc[n])
	{
		free_matc(matc[n]);
		n++;
	}
	free(matc);
}
