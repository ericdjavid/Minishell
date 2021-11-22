/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/22 15:30:50 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status = 0;

int	main(int ac, char **av, char **envp)
{
	char		*cmd_line;
	char		**paths;
    t_control   *list;
	int			i;

	(void)av;
	if (ac != 1)
		return (1);
    list = ft_init();
    if (!list)
		return (-1);
	i = -1;
    while (envp[++i])
		add_end_list(envp[i], list);	
	paths = init_paths(envp); 
	cmd_line = prompt_msg();
	while (cmd_line)
	{
		exec_cmd(cmd_line, paths, list);
		free(cmd_line);
		cmd_line = prompt_msg();
	}
	free_matc(paths);
	return (status);
}
