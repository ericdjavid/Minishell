/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_configs_rdin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:32:02 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 15:21:14 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_configs_rdin(char ***newargv, char **files, char **heredoc, int *c)
{
	if (c[1] == 1)
	{
		if (!make_config_1(heredoc, (*newargv)[c[0] + 1], &c[2]))
		{
			return (0);
		}
		if (newargv[c[0]] && !ft_strncmp(*newargv[c[0]], "<<",
				ft_strlen(*newargv[c[0]])))
		{
			free(*heredoc);
			*heredoc = NULL;
			g_status = 0;
			return (0);
		}
	}
	else
	{
		if (!make_config_2(files, (*newargv)[c[0] + 1], &c[2]))
			return (0);
	}
	return (1);
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

char	*print_error_rdin(int ret, char *lim, char *heredoc)
{
	ft_printf_fd(2,
		"minishell: warning: here-document at line %d", ret);
	ft_printf_fd(2, " delimited by end-of-file (wanted `%s')\n", lim);
	return (heredoc);
}
