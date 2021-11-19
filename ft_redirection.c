/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:58:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/19 20:45:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(char ***newargv, int n_n)
{
	int	c;
	int	fd;

	c = 0;
	while (newargv[n_n][c])
	{
		if (!ft_strncmp(newargv[n_n][c], ">", ft_strlen(newargv[n_n][c])))
		{
			fd = get_outfd(newargv[n_n][c + 1]);
			if (fd < 0)
				return (fd);
			newargv[n_n] = get_new_redir(newargv[n_n]);
			if (!newargv[n_n])
				return (0);
			ft_dup2(fd, STDOUT_FILENO);
			ft_close_fd(fd);
			return (2);
		}
		c++;
	}
	return (1);
}

int	get_outfd(char *file)
{
	int	outfd;

	if (!file)
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token newline\n");
		return (-2);
	}
	if (!access(file, F_OK))
	{
		if (!access(file, W_OK))
		{
			outfd = open(file, O_TRUNC | O_WRONLY);
		}
		else
		{
			outfd = -1;
			ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
		}
	}
	else
	{
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	}
	return (outfd);
}

char	**get_new_redir(char **newargv)
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
		new[c_2] = ft_strdup(newargv[c]);
		if (!new[c_2])
			return (free_redirection(newargv, new));
		c_2++;
		c++;
		if (newargv[c] && !ft_strncmp(newargv[c], ">", ft_strlen(newargv[c])))
			c += 2;
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
