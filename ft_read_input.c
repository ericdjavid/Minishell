/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:02:04 by abrun             #+#    #+#             */
/*   Updated: 2022/01/10 12:21:48 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (exit_readin(files, heredoc, -1));
		else if (c[1])
		{
			if (!make_configs_rdin(newargv, files, &heredoc, &c[0]))
				return (exit_readin(files, heredoc, 0));
			(*newargv) = get_newargv_rdin((*newargv), c[0], paths);
			if (!(*newargv))
				return (exit_readin(files, heredoc, 0));
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
	if (!files)
		return (0);
	*files = 0;
	return (files);
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
	if (!config)
		*c += 1;
	return (config);
}
