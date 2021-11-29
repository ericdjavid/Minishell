/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/21 20:58:57 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(char ***newargv, int n_n)
{
	int	c;
	int	fd;
	int	config;
	int	ret;

	c = 0;
	ret = 0;
	while (newargv[n_n][c])
	{
		if (!ft_strncmp(newargv[n_n][c], ">", ft_strlen(newargv[n_n][c]))
			|| !ft_strncmp(newargv[n_n][c], "<", ft_strlen(newargv[n_n][c])))
		{
			if (newargv[n_n][c][0] == '>')
				config = 3;
			else
				config = 2;
			fd = get_outfd(newargv[n_n][c + 1], config);
			if (fd < 0)
				return (fd);
			newargv[n_n] = get_new_redir(newargv[n_n], c);
			if (!newargv[n_n])
				return (0);
			if (config == 3)
				ft_dup2(fd, STDOUT_FILENO);
			else
				ft_dup2(fd, STDIN_FILENO);
			ft_close_fd(fd);
			if (ret != config && ret < 5)
				ret += config;
			c--;
		}
		c++;
	}
	if (ret)
		return (ret);
	return (1);
}

int	get_outfd(char *file, int config)
{
	int	outfd;

	outfd = -1;
	if (!file)
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token newline\n");
		return (-2);
	}
	if (!access(file, F_OK))
	{
		if (config == 3 && !access(file, W_OK))
			outfd = open(file, O_TRUNC | O_WRONLY);
		else if (config == 2 && !access(file, R_OK))
			outfd = open(file, O_TRUNC | O_RDONLY);
		else
			ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
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