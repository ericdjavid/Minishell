/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:10:52 by abrun             #+#    #+#             */
/*   Updated: 2021/12/28 16:54:07 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths, t_control *list)
{
	char	***newargv;
	char	*new_line;
	int		ret;

	ret = 1;
	while (*cmd_line && *cmd_line == 32)
		cmd_line++;
	if (!*cmd_line)
		return (1);
	new_line = get_new_line(cmd_line, list);
	if (!new_line)
		return (-1);
	newargv = init_newargv(new_line, paths);
	if (!newargv)
	{
		free(new_line);
		return (-1);
	}
	// if (ft_bad_entries(newargv) == TRUE)
	// 	return (-2);
	if (ft_3dimlen(newargv + 1) == 1 && is_builtins(newargv[1][0]))
		ret = exec_builtins(&newargv[1], list, paths);
	else
		ft_cmd(newargv, paths, list, n_pid(newargv));
	return (exit_exec(ret, newargv, new_line));
}

char	*get_new_line(char *cmd_line, t_control *list)
{
	char	*new_line;

	new_line = ft_strdup(cmd_line);
	if (!new_line)
		return (0);
	new_line = ft_is_dollar2(new_line, list);
	new_line = put_sp_around_pipes(new_line);
	if (!new_line)
		return (0);
	return (new_line);
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

char	*put_sp_around_pipes(char *str)
{
	char	*new;
	int		c_1;
	int		c_2;

	new = init_param_put_sp(str);
	if (!new)
		return (0);
	c_2 = 0;
	c_1 = 0;
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

char	*init_param_put_sp(char *str)
{
	char	*new;
	int		c_1;
	int		c_2;

	if (!str)
		return (0);
	c_2 = 0;
	c_1 = 0;
	while (str[c_1])
	{
		if (str[c_1] == '|')
			c_2 += 2;
		c_1++;
	}
	new = malloc(c_1 + c_2 + 1);
	if (!new)
	{
		free(str);
		return (0);
	}
	return (new);
}
