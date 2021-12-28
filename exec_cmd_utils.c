/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:02:41 by abrun             #+#    #+#             */
/*   Updated: 2021/12/28 15:22:47 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_pid(char ***newargv)
{
	int	c;

	c = 1;
	while (newargv[c])
		c++;
	return (c);
}

int	exit_exec(int ret, char ***newargv, char *new_line)
{
	free_newargv(newargv);
	free(new_line);
	return (ret);
}
