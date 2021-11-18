/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:56:08 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 12:34:41 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***init_newargv(char *cmd_line, char **paths)
{
	char	***newargv;
	int		c_1;
	int		c_2;
	int		n_cmd;
	char		**split;

	n_cmd = get_n_cmd(cmd_line);
	newargv = malloc(sizeof(char **) * (n_cmd + 1));
	if (!newargv)
		return (0);
	split = ft_split(cmd_line, 32);
	if (!split)
	{
		free_3dim_matc(newargv);
		return (0);
	}
	c_1 = -1;
	while (++c_1 < n_cmd)
	{
		newargv[c_1] = malloc(sizeof(char *) * (ft_split_len(split) + 1));
		if (!newargv[c_1])
		{
			free_3dim_matc(newargv);
			free_matc(split);
			return (0);
		}
		c_2 = 0;
		while (*split && ft_strncmp(*split, "|", ft_strlen(*split)))
		{
			newargv[c_1][c_2] = *split;
			split++;
			c_2++;
		}
		if (!is_builtins(newargv[c_1][0]))
			newargv[c_1][0] = init_cmd_path(newargv[c_1][0], paths);
		if (c_1 + 1 < n_cmd)
			free(*split);
		split++;
		newargv[c_1][c_2] = 0;
	}
	newargv[c_1] = 0;
	//free(split);
	return (newargv);
}

int	ft_split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len] && ft_strncmp(split[len], "|", ft_strlen(split[len])))
		len++;
	return (len);
}
