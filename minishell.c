/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/19 19:30:58 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*cmd_line;
	char	**paths;

	(void)av;
	if (ac != 1)
		return (1);
	paths = init_paths(envp); 

	cmd_line = prompt_msg();
	while (cmd_line)
	{
		exec_cmd(cmd_line, paths);
		free(cmd_line);
		cmd_line = prompt_msg();
	}
	free_matc(paths);
	return (0);
}
