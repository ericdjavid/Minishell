/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2022/01/05 13:00:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_redirection(char ***newargv, int *ret)
{
	int	c;
	int	config;
	int	*box;

	c = 0;
	box = malloc(sizeof(int) * 4);
	while (c < 4)
		box[c++] = 0;
	c = 0;
	while ((*newargv)[c])
	{
		config = which_redirection((*newargv)[c]);
		if (config)
		{
			newargv = loop_redirection(newargv, config, box, c);
			if (!newargv)
				return (0);
		}
		else
			c++;
	}
	return (exit_redirection(box, ret));
}

char	***loop_redirection(char ***newargv, int config, int *box, int c)
{
	int	fd;

	fd = get_outfd((*newargv)[c + 1], config);
	if (fd < 0)
	{
		free(box);
		return (0);
	}
	*newargv = get_new_redir(*newargv, c);
	if (!(*newargv))
	{
		ft_close_fd(fd);
		free(box);
		return (0);
	}
	box = assign_config(box, config);
	if (config == 3 || config == 4)
	{
		if (ft_strncmp(**newargv, "echo", ft_strlen(**newargv)))
			ft_dup2(fd, STDOUT_FILENO);
		box[3] = fd;
	}
	ft_close_fd(fd);
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
		ft_printf_fd(2, "minishell: syntax error");
		ft_printf_fd(2, " near unexpected token newline\n");
		g_status = 258;
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
	else
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
		g_status = 1;
	}
	return (outfd);
}
