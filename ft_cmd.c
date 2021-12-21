/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:13:57 by abrun             #+#    #+#             */
/*   Updated: 2021/12/21 18:00:49 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(char ***newargv, char **paths, t_control *list)
{
	int		n_newargv;
	int		**fds;
	pid_t	child_pid;

	n_newargv = 1;
	fds = init_fds();
	if (!fds)
		return (0);
		// TODO: deal with it
	ft_add_new_var(list, DEAL_ENV);
	ft_add_new_var(list, DEAL_EXPORT);
	while (newargv[n_newargv])
	{
		if (pipe(fds[0]) == -1)
			return (0);
		if (!ft_strncmp(newargv[n_newargv][0], "export",
			ft_strlen(newargv[n_newargv][0])) && newargv[n_newargv][1])
			ft_get_new_var(list, newargv[n_newargv]);
		if (!ft_strncmp(newargv[n_newargv][0], "unset",
			ft_strlen(newargv[n_newargv][0])) && newargv[n_newargv][1])
			ft_unset(list, newargv[n_newargv]);
		child_pid = fork();
		if (child_pid == -1)
			return (0);
		if (child_pid == 0)
			if (!(ft_child(&newargv[n_newargv], paths, list, fds)))
				return (status_free(fds));
		ft_close_fd(fds[0][1]);
		while (wait(&status) > 0)
			;
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 131)
			write(1, "\n", 1);
		fds[1][0] = fds[0][0];
		n_newargv++;
	}
	return (status_free(fds));
}

int	*init_ret(void)
{
	int	*ret;

	ret = malloc(sizeof(int) * 2);
	if (!ret)
		return (0);
	ret[0] = 1;
	ret[1] = 1;
	return (ret);
}

int	**init_fds(void)
{
	int	**fds;

	fds = malloc(sizeof(int *) * 2);
	if (!fds)
		return (0);
	fds[0] = malloc(sizeof(int) * 2);
	if (!fds[0])
	{
		free(fds);
		return (0);
	}
	fds[1] = malloc(sizeof(int));
	if (!fds[1])
	{
		free(fds[0]);
		free(fds);
		return (0);
	}
	fds[1][0] = 0;
	return (fds);
}

int	status_free(int **fds)
{
	free_mati(fds, 2);
	return (status);
}

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
