/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2022/01/10 12:23:18 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_redirection(char ***newargv, int *ret, int forked)
{
	int	c;
	int	*box;

	c = 0;
	box = malloc(sizeof(int) * 4);
	if (!box)
		return (ret);
	while (c < 4)
		box[c++] = 0;
	c = 0;
	while ((*newargv) && (*newargv)[c])
	{
		if (which_redirection((*newargv)[c]))
		{
			newargv = loop_redirection(newargv, box, c, forked);
			if (!newargv)
				return (exit_redirection(box, ret));
		}
		else
			c++;
	}
	return (exit_redirection(box, ret));
}

char	***loop_redirection(char ***newargv, int *box, int c, int forked)
{
	int	fd;
	int	config;

	config = which_redirection((*newargv)[c]);
	fd = get_outfd((*newargv)[c + 1], config);
	if (fd < 0)
		return (exit_fd_neg(box, *newargv));
	*newargv = get_new_redir(*newargv, c);
	if (!(*newargv))
	{
		ft_close_fd(fd);
		return (0);
	}
	if (is_other_wrout(*newargv))
	{
		ft_close_fd(fd);
		return (newargv);
	}
	box = assign_config(box, config, fd);
	if (forked)
	{
		ft_dup2(fd, STDOUT_FILENO);
		ft_close_fd(fd);
	}
	return (newargv);
}

int	which_redirection(char *s)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!ft_strncmp(s, ">", s_len))
		return (3);
	else if (!ft_strncmp(s, ">>", s_len))
		return (4);
	return (0);
}

int	get_outfd(char *file, int config)
{
	int	outfd;

	outfd = -1;
	if (!file)
	{
		ft_printf_fd(2, "minishell: syntax error\n");
		g_status = 2;
		return (-2);
	}
	else if (!access(file, F_OK))
	{
		outfd = get_outfd_2(file, config);
	}
	else if (config != 2)
	{
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	}
	else
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			file);
	}
	return (outfd);
}

int	get_outfd_2(char *file, int config)
{
	int	outfd;

	outfd = -1;
	if (config == 3 && !access(file, W_OK))
		outfd = open(file, O_TRUNC | O_WRONLY);
	else if (config == 4 && !access(file, W_OK))
		outfd = open(file, O_WRONLY | O_APPEND);
	else if (config == 2 && !access(file, R_OK))
		outfd = open(file, O_RDONLY);
	else
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
		g_status = 1;
	}
	return (outfd);
}
