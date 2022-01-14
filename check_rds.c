/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:52:12 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 11:08:01 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rds_ok(char *cmd, int c, char k)
{
	int		c_2;

	c_2 = 0;
	while (c_2 < c)
	{
		if (cmd[c_2] == '"' || cmd[c_2] == '\'')
		{
			k = cmd[c_2++];
			while (cmd[c_2] && cmd[c_2] != k)
				c_2++;
			if (c_2 > c)
				return (1);
		}
		c_2++;
	}
	if (!cmd[c + 1])
		return (0);
	if (cmd[c + 1] == k)
		c++;
	if (!cmd[c + 1])
		return (0);
	if (cmd[++c]
		&& (cmd[c] == '<' || cmd[c] == '>' || cmd[c] == '|'))
		return (0);
	return (1);
}

int	check_rds(char *cmd)
{
	int	c;

	c = 0;
	while (cmd[c])
	{
		if ((cmd[c] == '>' || cmd[c] == '<' || cmd[c] == '|'))
		{
			if (!rds_ok(cmd, c, cmd[c]))
			{
				write(2, "minishell: error parse\n", 23);
				g_status = 2;
				return (0);
			}
			else if (cmd[c] == cmd[c + 1])
				c++;
		}
		c++;
	}
	return (1);
}
