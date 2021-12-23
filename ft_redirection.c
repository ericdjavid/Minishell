/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2021/12/23 18:57:54 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(char ***newargv)
{
	int	c;
	int	fd;
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
			fd = get_outfd((*newargv)[c + 1], config);
			if (fd < 0)
				return (0);
			*newargv = get_new_redir(*newargv, c);
			if (!(*newargv))
				return (0);
			if (config == 3 || config == 4)
				ft_dup2(fd, STDOUT_FILENO);
			else
				ft_dup2(fd, STDIN_FILENO);
			ft_close_fd(fd);
			ret = assign_config(ret, config);
		}
		else
			c++;
	}
	return (exit_redirection(ret));
}

int	which_redirection(char *s)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!ft_strncmp(s, ">", s_len))
		return (3);
	else if (!ft_strncmp(s, "<", s_len))
		return (2);
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
		ft_printf_fd(2, "minishell: syntax error near unexpected token newline\n");
		status = 258;
		return (-2);
	}
	if (!access(file, F_OK))
	{
		if (config == 3 && !access(file, W_OK))
			outfd = open(file, O_TRUNC | O_WRONLY);
		else if (config == 2 && !access(file, R_OK))
			outfd = open(file, O_TRUNC | O_RDONLY);
		else if (config == 4 && !access(file, W_OK))
			outfd = open(file, O_WRONLY | O_APPEND);
		else
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
			status = 1;
		}
	}
	else
	{
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	}
	return (outfd);
}

char	**get_new_redir(char **newargv, int redir)
{
	char	**new;
	int		c;
	int		c_2;

	new = malloc(sizeof(char *) * ft_matlen(newargv));
	if (!new)
		return (free_redirection(newargv, new));
	c = 0;
	c_2 = 0;
	while (newargv[c])
	{
		if (c == redir)
			c += 2;
		if (newargv[c])
		{
			new[c_2] = ft_strdup(newargv[c]);
			if (!new[c_2])
				return (free_redirection(newargv, new));
			c_2++;
			c++;
		}
	}
	new[c_2] = 0;
	free_matc(newargv);
	return (new);
}

char	**free_redirection(char **newargv, char **new)
{
	free_matc(newargv);
	free_matc(new);
	return (0);
}

int	*assign_config(int *ret, int config)
{
	if (config == 2)
		ret[0] = 1;
	if (config == 3)
		ret[1] = 1;
	if (config == 4)
		ret[2] = 1;
	return (ret);
}

int	exit_redirection(int *ret)
{
	int	c;
	int	value;

	c = 0;
	value = 0;
	while (c < 3)
	{
		value += (ret[c] * (c + 2));
		c++;
	}
	free(ret);
	if (!value)
		return (1);
	return (value);
}
