/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:02:04 by abrun             #+#    #+#             */
/*   Updated: 2021/11/24 16:58:21 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_input(char ***newargv, int n_newargv, char **paths)
{
	char	*heredoc;
	int		c;
	int		fds[2];

	c = 0;
	while (newargv[n_newargv][c])
	{
		if (!ft_strncmp(newargv[n_newargv][c], "<<",
				ft_strlen(newargv[n_newargv][c])))
		{
			if (!newargv[n_newargv][c + 1])
				return (0);
			heredoc = get_heredoc(newargv[n_newargv][c + 1]);
			if (!heredoc)
				return (0);
			if (pipe(fds) == -1)
				return (0);
			ft_dup2(fds[0], STDIN_FILENO);
			write(fds[1], heredoc, ft_strlen(heredoc));
			ft_close_fd(fds[1]);
			ft_close_fd(fds[0]);
			newargv[n_newargv] = get_newargv_rdin(newargv[n_newargv],
					c, paths);
			if (!newargv[n_newargv])
				return (0);
			return (2);
		}
		c++;
	}
	return (1);
}

char	*get_heredoc(char *lim)
{
	char	*heredoc;
	char	*buf;
	int		ret;

	heredoc = malloc(1);
	if (!heredoc)
		return (0);
	heredoc[0] = 0;
	ret = 1;
	status = 9;
	while (ret)
	{
		buf = readline("> ");
		if (!buf)
		{
			ft_printf_fd(2, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `l')\n", ret, lim);
			return (heredoc);
		}
		if (ft_strncmp(buf, lim, ft_strlen(lim)))
			heredoc = ft_strjoin_free_n(heredoc, buf);
		else
			ret = 0;
		if (buf)
			free(buf);
		if (ret)
			ret++;
	}
	heredoc[ft_strlen(heredoc)] = 0;
	return (heredoc);
}

char	**get_newargv_rdin(char **newargv, int c, char **paths)
{
	char	**new;
	int		c_2;
	int		c_3;

	new = malloc(sizeof(char *) *(ft_matlen(newargv) - 1));
	if (!new)
	{
		free_matc(newargv);
		return (0);
	}
	c_2 = 0;
	c_3 = 0;
	while (newargv[c_2])
	{
		if (c_2 == c)
			c_2 += 2;
		new[c_3] = ft_strdup_rdin(newargv[c_2], newargv, new);
		if (!new[c_3])
			return (0);
		if (c_3 == c)
		{
			new[c_3] = init_cmd_path(new[c_3], paths);
			if (!new[c_3])
				return (0);
		}
		c_2++;
		c_3++;
	}
	new[c_3] = 0;
	free_matc(newargv);
	return (new);
}

char	*ft_strdup_rdin(char *s, char **mat1, char **mat2)
{
	char	*res;

	res = ft_strdup(s);
	if (!res)
	{
		free_matc(mat1);
		free_matc(mat2);
		return (0);
	}
	return (res);
}
