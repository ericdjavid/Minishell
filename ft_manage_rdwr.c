/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_rdwr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:19:39 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 15:25:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_ret2(void)
{
	int	*ret;

	ret = malloc(sizeof(int) * 3);
	if (!ret)
		return (0);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	return (ret);
}

int	*exit_manage_rdwr(int *ret, t_file *files)
{
	free(ret);
	ft_clearfiles(&files);
	return (0);
}

int	add_file(char *file, int config, t_file **files)
{
	t_file	*new;

	new = ft_filenew(file, config);
	if (!new)
		return (0);
	if (config == 1)
		new->heredoc = get_heredoc(file);
	ft_fileadd_back(files, new);
	return (1);
}

char	**exit_get_newrdwr(char **old, char **new)
{
	if (new)
		free_matc(new);
	free_matc(old);
	return (0);
}

char	**get_newargv_rdwr(char **old, int c)
{
	char	**new;
	int		c_2;
	int		i;

	new = malloc(sizeof(char *) * (ft_matlen(old) - 1));
	if (!new)
		return (exit_get_newrdwr(old, new));
	c_2 = 0;
	i = 0;
	while (old[c_2 + i])
	{
		if (i || c_2 != c)
		{
			new[c_2] = ft_strdup(old[c_2 + i]);
			if (!new[c_2])
				return (exit_get_newrdwr(old, new));
			c_2++;
		}
		else
			i = 2;
	}
	new[c_2] = 0;
	free_matc(old);
	return (new);
}

int	get_config(char *s)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!ft_strncmp(s, "<<", s_len))
		return (1);
	if (!ft_strncmp(s, "<", s_len))
		return (2);
	if (!ft_strncmp(s, ">", s_len))
		return (3);
	else if (!ft_strncmp(s, ">>", s_len))
		return (4);
	return (0);
}

int	get_inout(int config)
{
	if (config >= 3)
		return (1);
	return (0);
}

int	is_other_rdwr(int inout, t_file *files)
{
	files = files->next;
	while (files)
	{
		if (inout && files->config >= 3)
			return (1);
		if (!inout && files->config <= 2)
			return (1);
		files = files->next;
	}
	return (0);
}

int	print_heredoc(char *heredoc, int *ret)
{
	int	pip[2];

	if (pipe(pip) == -1)
		return (0);
	write(pip[1], heredoc, ft_strlen(heredoc));
	ft_dup2(pip[0], STDIN_FILENO);
	ft_close_fd(pip[0]);
	ft_close_fd(pip[1]);
	ret[0] = 1;
	return (1);
}

int	*make_dups_rdwr(t_file *files, int *ret, int forked)
{
	t_file	*first;
	int		fds[2];
	int		inout;

	first = files;
	fds[0] = -1;
	fds[1] = -1;
	while (files)
	{
		inout = get_inout(files->config);
		if (files->config != 1)
		{
			fds[inout] = get_outfd(files->name, files->config);
			if (fds[inout] < 0)
			{
				if (fds[!inout] > 0)
					ft_close_fd(fds[!inout]);
				ft_clearfiles(&first);
				free(ret);
				if (forked)
					ft_close_fd(0);
				return (0);
			}
			if (is_other_rdwr(inout, files))
				ft_close_fd(fds[inout]);
		}
		else if (!is_other_rdwr(inout, files))
		{
			if (!print_heredoc(files->heredoc, ret))
			{
				if (fds[!inout] > 0)
					ft_close_fd(fds[!inout]);
				ft_clearfiles(&first);
				free(ret);
				return (0);
			}
		}			
		files = files->next;
	}
	if (fds[0] > 0)
	{
		ret[0] = 1;
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
	ft_clearfiles(&first);
	return (ret);
}

int	*ft_manage_rdwr(char ***newargv, int forked)
{
	t_file	*files;
	int		c;
	int		*ret;
	int		config;

	files = NULL;
	ret = init_ret2();
	if (!ret)
		return (0);
	c = 0;
	while ((*newargv)[c])
	{
		config = get_config((*newargv)[c]);
		if (config)
		{
			if (!add_file((*newargv)[c + 1], config, &files))
				return (exit_manage_rdwr(ret, files));
			(*newargv) = get_newargv_rdwr(*newargv, c);
			if (!(*newargv))
				return (exit_manage_rdwr(ret, files));
		}
		else
			c++;
	}
	return (make_dups_rdwr(files, ret, forked));
}
