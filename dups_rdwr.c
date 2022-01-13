/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_rdwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:34:16 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 18:34:55 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*make_dups_rdwr(t_file *files, int *ret, int forked, char *cmd)
{
	int	*fds;

	fds = fill_fds_rdwr(files, ret, forked);
	if (!fds)
		return (exit_dups_rdwr(ret, files));
	if (fds[0] > 0)
	{
		ret[0] = 1;
		if (!is_builtins(cmd))
			ft_dup2(fds[0], STDIN_FILENO);
		ft_close_fd(fds[0]);
	}
	if (fds[1] > 0)
	{
		ret[1] = fds[1];
		if (forked)
		{
			ft_dup2(fds[1], STDOUT_FILENO);
			ft_close_fd(fds[1]);
		}
	}
	ft_clearfiles(&files);
	free(fds);
	return (ret);
}

int	*fill_fds_rdwr(t_file *files, int *ret, int forked)
{
	int	*fds;
	int	inout;

	fds = init_fds_rdwr();
	while (files)
	{
		inout = get_inout(files->config);
		if (files->config != 1)
		{
			fds[inout] = get_outfd(files->name, files->config);
			if (fds[inout] < 0)
				return (fd_is_negative(fds, inout, forked));
			if (is_other_rdwr(inout, files))
				ft_close_fd(fds[inout]);
		}
		else if (!is_other_rdwr(inout, files))
		{
			if (!print_heredoc(files->heredoc, ret, fds, inout))
				return (malloc_failed());
		}
		files = files->next;
	}
	return (fds);
}

int	print_heredoc(char *heredoc, int *ret, int *fds, int inout)
{
	int	pip[2];

	if (pipe(pip) == -1)
	{
		if (fds[!inout] > 0)
			ft_close_fd(fds[!inout]);
		free(fds);
		return (0);
	}
	write(pip[1], heredoc, ft_strlen(heredoc));
	ft_dup2(pip[0], STDIN_FILENO);
	ft_close_fd(pip[0]);
	ft_close_fd(pip[1]);
	ret[0] = 1;
	return (1);
}

int	*init_fds_rdwr(void)
{
	int	*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		return (malloc_failed());
	fds[0] = -1;
	fds[1] = -1;
	return (fds);
}

int	*fd_is_negative(int *fds, int inout, int forked)
{
	if (fds[!inout] > 0)
		ft_close_fd(fds[!inout]);
	free(fds);
	if (forked)
		ft_close_fd(0);
	return (0);
}
