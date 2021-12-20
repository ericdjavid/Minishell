/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 16:24:00 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  when deleting the folder where we are and pwd
// pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
int	ft_child(char ***newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;

	signal(SIGQUIT, SIG_DFL);
	ret = ft_manage_fds(newargv, paths, fds);
	if (!ret)
		exit(status);
	else if (ft_builtins(*newargv, list))
		;
	else if (access((*newargv)[0], F_OK))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
			(*newargv)[0]);
		status = 127;
	}
	else if (access((*newargv)[0], X_OK))
	{
		ft_printf_fd(2, "minishell: permission non accordée: %s\n",
			(*newargv)[0]);
		status = 126;
	}
	else if (execve((*newargv)[0],
	// rmplcacer NULL par les vars d env avec une valeur
	//  incrementer SHLVL au debut de minishell (si aucun set 1)
		(*newargv), NULL) < 0)
		status = 1;
	free(ret);
	exit(status);
}

