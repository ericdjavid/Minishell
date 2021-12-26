/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:02:04 by abrun             #+#    #+#             */
/*   Updated: 2021/12/26 18:54:55 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unexpected(char *arg)
{
	if (!arg || *arg == 28 || *arg == 29 || *arg == '<'
		|| *arg == '>' || *arg == '|')
		return (1);
	return (0);
}

int	init_config(char **newargv, int *c)
{
	int	config;

	config = 0;
	if (!ft_strncmp(newargv[*c], "<<",
			ft_strlen(newargv[*c])))
		config = 1;
	else if (!ft_strncmp(newargv[*c], "<",
			ft_strlen(newargv[*c])))
		config = 2;
	if (config && is_unexpected(newargv[*c + 1]))
	{
		if (newargv[*c + 1])
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%s'\n",
				newargv[*c + 1]);
		else
			write(2,
				"minishell: syntax error near unexpected token `newline'\n", 56);
		return (-1);
	}
	if (!config)
		*c += 1;
	return (config);
}

int	exit_readin(char **files, char *heredoc)
{
	free_matc(files);
	if (heredoc)
		free(heredoc);
	return (0);
}

int	make_config_1(char **heredoc, char *lim, int *last)
{
	if (*heredoc)
		free(*heredoc);
	*heredoc = get_heredoc(lim);
	if (!*heredoc)
		return (0);
	*last = 1;
	return (1);
}

int	make_config_2(char **files, char *arg, int *last)
{
	static int	n_f = 0;

	files[n_f] = ft_strdup(arg);
	if (!files[n_f])
		return (0);
	*last = 2;
	n_f++;
	files[n_f] = 0;
	return (1);
}

int	dup_readin_2(char **heredoc, char ***files, int last, int fdin)
{
	int	fds[2];

	if (*heredoc && last == 1)
	{
		if (pipe(fds) == -1)
			return (exit_readin(*files, *heredoc));
		write(fds[1], *heredoc, ft_strlen(*heredoc));
		ft_dup2(fds[0], STDIN_FILENO);
		ft_close_fd(fds[0]);
		ft_close_fd(fds[1]);
		return (2);
	}
	else if (last == 2)
	{
		ft_dup2(fdin, STDIN_FILENO);
		ft_close_fd(fdin);
		return (2);
	}
	return (1);
}

int	dup_readin(char ***files, char **heredoc, int last)
{
	int	fdin;
	int	c;

	c = 0;
	while ((*files)[c])
	{
		fdin = get_outfd((*files)[c], 2);
		if (fdin < 0)
			return (exit_readin(*files, *heredoc));
		c++;
	}
	return (dup_readin_2(heredoc, files, last, fdin));
}

int	make_configs_rdin(char ***newargv, char **files, char **heredoc, int *c)
{
	if (c[1] == 1)
	{
		if (!make_config_1(heredoc, (*newargv)[c[0] + 1], &c[2]))
			return (0);
	}
	else
	{
		if (!make_config_2(files, (*newargv)[c[0] + 1], &c[2]))
			return (0);
	}
	return (1);
}

int	ft_read_input(char ***newargv, char **paths)
{
	char	*heredoc;
	char	**files;
	int		c[3];

	c[0] = 0;
	c[2] = 0;
	heredoc = NULL;
	files = init_files(*newargv);
	if (!files)
		return (0);
	while ((*newargv)[c[0]])
	{
		c[1] = init_config(*newargv, &c[0]);
		if (c[1] < 0)
			return (exit_readin(files, heredoc));
		else if (c[1])
		{
			if (!make_configs_rdin(newargv, files, &heredoc, &c[0]))
				return (exit_readin(files, heredoc));
			(*newargv) = get_newargv_rdin((*newargv), c[0], paths);
			if (!(*newargv))
				return (exit_readin(files, heredoc));
		}
	}
	return (dup_readin(&files, &heredoc, c[2]));
}

char	**init_files(char **newargv)
{
	char	**files;
	int		n_files;
	int		c;

	c = 0;
	n_files = 0;
	while (newargv[c])
	{
		if (!ft_strncmp(newargv[c], "<", ft_strlen(newargv[c])))
			n_files++;
		c++;
	}
	files = malloc(sizeof(char *) * (n_files + 1));
	*files = 0;
	return (files);
}

char	*print_error_rdin(int ret, char *lim, char *heredoc)
{
	ft_printf_fd(2,
		"minishell: warning: here-document at line %d", ret);
	ft_printf_fd(2, " delimited by end-of-file (wanted `l')\n", lim);
	return (heredoc);
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
	g_status = 9;
	while (ret)
	{
		buf = readline("> ");
		if (!buf)
			return (print_error_rdin(ret, lim, heredoc));
		else if (!*buf || ft_strncmp(buf, lim, ft_strlen(buf)))
			heredoc = ft_strjoin_free_n(heredoc, buf);
		else
			ret = 0;
		free(buf);
		if (ret)
			ret++;
	}
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
		if (newargv[c_2])
		{
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
