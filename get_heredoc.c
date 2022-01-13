/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:32:02 by abrun             #+#    #+#             */
/*   Updated: 2022/01/13 14:46:37 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
