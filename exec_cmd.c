/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:10:52 by abrun             #+#    #+#             */
/*   Updated: 2021/12/21 16:55:30 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths, t_control *list)
{
	char	***newargv;
	int		newargv_len;
	char	*new_line;

	if (ft_bad_entries(cmd_line) == TRUE)
		return (-2);
	if (!*cmd_line)
		return (1);
	new_line = ft_strdup(cmd_line);
	if (!new_line)
		return (-1);
	new_line = ft_is_dollar2(new_line, list);
	if (!new_line)
		return (-1);
	new_line = put_spAroundPipes(new_line);
	if (!new_line)
		return (-1);
	newargv = init_newargv(new_line, paths);
	if (!newargv)
		return (-1);
	newargv_len = ft_3dimlen(newargv + 1);
	//TODO : Fix free pbm with exit
	if (newargv_len == 1 && !ft_strncmp(newargv[1][0], "exit", 4))
	{
		free(new_line);
		write(1, "exit\n", 5);
		return (ft_exit(newargv[1]) - 1);
	}
	if (newargv_len == 1 && !ft_strncmp(newargv[1][0], "cd", 3))
		ft_cd(newargv[1]);
	else
		ft_cmd(newargv, paths, list);
	free_newargv(newargv);
	free(new_line);
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

char	*put_spAroundPipes(char *str)
{
	char	*new;
	int		c_1;
	int		c_2;

	c_2 = 0;
	c_1 = 0;
	while (str[c_1])
	{
		if (str[c_1] == '|')
			c_2 += 2;
		c_1++;
	}
	if (!c_2)
		return (str);
	new = malloc(c_1 + c_2 + 1);
	if (!new)
		return (0);
	c_1 = 0;
	c_2 = 0;
	while (str[c_1])
	{
		if (str[c_1] == '|')
		{
			new[c_1 + c_2++] = 32;
			new[c_1 + c_2++] = '|';
			new[c_1 + c_2] = 32;
		}
		else
			new[c_1 + c_2] = str[c_1];
		c_1++;
	}
	new[c_1 + c_2] = 0;
	free(str);
	return (new);
}
