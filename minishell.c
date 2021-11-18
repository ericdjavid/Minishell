/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 10:37:23 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **envp)
{
	char		*cmd_line;
	char		**paths;
    t_control   *list;
	// int			i;

	if (ac != 1)
		return (1);
    // if (!list)
	// 	return (-1);
	// i = -1;
    // while (envp[++i])
	// 	add_end_list(envp[i], list);	
	paths = init_paths(envp); 
	cmd_line = prompt_msg();
    list = ft_init();
	while (cmd_line)
	{
		// TODO: faire avec des pipes multiples
		exec_cmd(cmd_line, paths, list);
		free(cmd_line);
		cmd_line = prompt_msg();
	}
	return (0);
}
