/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:10:39 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/14 11:08:43 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths, t_control *list)
{
	char	***newargv;
	char	*new_line;
	int		ret;
	int		i;

	ret = 2;
	i = 0;
	while (*cmd_line && *cmd_line == 32)
		cmd_line++;
	if (!*cmd_line || !check_rds(cmd_line))
		return (1);
	new_line = get_new_line(cmd_line, list, &i);
	if (i == 1 || !new_line)
		return (-2);
	newargv = init_newargv(new_line, paths);
	if (!newargv)
	{
		free(new_line);
		return (-1);
	}
	if (ft_3dimlen(newargv + 1) == 1 && is_builtins(newargv[1][0]))
		ret = exec_builtins(newargv[1], list, paths);
	else
		ft_cmd(newargv, paths, list, n_pid(newargv));
	return (exit_exec(ret, newargv, new_line));
}

int	ft_deal_bad_sq_dq(char *str)
{
	int		c;
	char	k;

	c = 0;
	while (str[c])
	{
		if (str[c] == '"' || str[c] == '\'')
		{
			k = str[c++];
			while (str[c] && str[c] != k)
				c++;
			if (str[c])
				c++;
			else
				return (0);
		}
		else
			c++;
	}
	return (1);
}

char	*get_new_line(char *cmd_line, t_control *list, int *i)
{
	char	*new_line;
	int		is_mal;
	int		count;

	count = 0;
	is_mal = 0;
	new_line = ft_strdup(cmd_line);
	if (!new_line)
		return (0);
	new_line = ft_is_dollar2(new_line, list, is_mal, count);
	if (!new_line)
		return (0);
	if (!ft_deal_bad_sq_dq(new_line))
	{
		free(new_line);
		*i = 1;
		ft_printf_fd(2, "minishell: error parsing <quotes>\n");
		return (0);
	}
	return (new_line);
}

void	free_newargv(char ***matc)
{
	int	n;

	n = 1;
	while (matc && matc[n])
	{
		free_matc(matc[n]);
		n++;
	}
	free(matc);
}
