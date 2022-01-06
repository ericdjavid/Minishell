/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:35:36 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 16:55:54 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_n_cmd(char *cmd_line)
{
	int	n_cmd;
	int	c;

	n_cmd = 1;
	c = 0;
	while (cmd_line[c])
	{
		if (cmd_line[c] == '|')
			n_cmd++;
		c++;
	}
	return (n_cmd);
}
