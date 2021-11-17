/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 14:09:30 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

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
		if (!exec_cmd(cmd_line, paths))
		{
			free_matc(paths);
			return (0);
		}
		cmd_line = prompt_msg();
	}
	return (0);
}
