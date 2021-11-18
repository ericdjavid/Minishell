/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:02:04 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 14:23:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_input(char **newargv, char **paths, int *fds)
{
	char	*heredoc;
	int		ret;
	char	**new;

	(void)fds;
	ret = 1;
	if (ft_strncmp(newargv[0], "<<", ft_strlen(newargv[0])))
		return (0);
	if (ft_matlen(newargv) < 3)
		return (0);
	heredoc = get_heredoc(newargv[1]);
	if (!heredoc)
		return (0);
	write(0, heredoc, ft_strlen(heredoc));
	new = init_new(newargv, paths);
	if (access(new[0], X_OK))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
				new[0]);
		ret = 127;
		exit(127);
	}
	else if (execve(new[0], new, NULL) == -1)
	{
		perror("nonono");
		ret = 1;
		exit (1);
	}
	return (ret);
}

char	*get_heredoc(char *lim)
{
	char	*heredoc;
	char	*buf;
	int		ret;
	int		lim_len;

	lim_len = init_param_heredoc(lim, &buf, &heredoc, &ret);
	if (!lim_len)
		return (0);
	write(STDOUT_FILENO, "> ", 2);
	while (ret > 0 || ret == -2)
	{
		if (ret != -2 && ft_strnstr(buf, "\n", lim_len))
			write(STDOUT_FILENO, "> ", 2);
		ret = read(STDOUT_FILENO, buf, lim_len);
		buf[ret] = 0;
		if (ft_strncmp(buf, lim, lim_len))
			heredoc = ft_strjoin_free(heredoc, buf);
		else
			ret = 0;
	}
	read(STDOUT_FILENO, buf, 1);
	free(buf);
	return (heredoc);
}

char	**init_new(char **newargv, char **paths)
{
	char	**new;
	int		c;

	new = malloc(sizeof(char *) * (ft_matlen(newargv) - 1));
	if (!new)
		return (0);
	c = 2;
	while (newargv[c])
	{
		new[c - 2] = ft_strdup(newargv[c]);
		if (!new[c - 2])
		{
			free_matc(new);
			return (0);
		}
		c++;
	}
	if (!is_builtins(new[0]))
			new[0] = init_cmd_path(new[0], paths);
	new[c - 2] = 0;
	return (new);
}

int	init_param_heredoc(char *lim, char **buf, char **heredoc, int *ret)
{
	int	lim_len;

	lim_len = ft_strlen(lim);
	*buf = malloc(lim_len + 1);
	if (!*buf)
		return (0);
	*heredoc = malloc(1);
	if (!*heredoc)
	{
		free(*buf);
		return (0);
	}
	**heredoc = 0;
	*ret = -2;
	return (lim_len);
}
