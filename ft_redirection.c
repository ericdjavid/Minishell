/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2022/01/04 16:35:46 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(char ***newargv)
{
	int	c;
	int	config;
	int	*ret;

	c = 0;
	ret = malloc(sizeof(int) * 3);
	while (c < 3)
		ret[c++] = 0;
	c = 0;
	while ((*newargv)[c])
	{
		config = which_redirection((*newargv)[c]);
		if (config)
		{
			newargv = loop_redirection(newargv, config, ret, c);
			if (!newargv)
				return (0);
		}
		else
			c++;
	}
	return (exit_redirection(ret));
}

char	***loop_redirection(char ***newargv, int config, int *ret, int c)
{
	int	fd;

	fd = get_outfd((*newargv)[c + 1], config);
	if (fd < 0)
	{
		free(ret);
		return (0);
	}
	*newargv = get_new_redir(*newargv, c);
	if (!(*newargv))
	{
		ft_close_fd(fd);
		free(ret);
		return (0);
	}
	if (config == 3 || config == 4)
		ft_dup2(fd, STDOUT_FILENO);
	ft_close_fd(fd);
	ret = assign_config(ret, config);
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
	else if (config == 2 && !access(file, R_OK))
		outfd = open(file, O_RDONLY);
	else if (config == 4 && !access(file, W_OK))
		outfd = open(file, O_WRONLY | O_APPEND);
	else
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
		g_status = 1;
	}
	return (outfd);
}
