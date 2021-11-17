/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 17:37:05 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
		return (1);
	(void)av;

	// TODO: essayer d'ouvrir le terminal sur Linux (ne marche pas sur mac)
//	if (!open_term())
//		return (1);

	char	*cmd_line;
	char	**paths;

	paths = init_paths(envp); 
	// TODO: donne moi ton avis sur l'affichage du prompt
	cmd_line = prompt_msg();
	while (cmd_line)
	{
		// TODO: faire avec des pipes multiples
		exec_cmd(cmd_line, paths);
		free(cmd_line);
		cmd_line = prompt_msg();
	}
	return (0);
}
