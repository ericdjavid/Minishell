/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:30:03 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/11 17:57:53 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_input(char ***nrv, char **paths)
{
	char	*heredoc;
	char	**files;
	int		c[3];

	heredoc = NULL;
	files = init_files(*nrv, c);
	if (!files)
		return (-1);
	while ((*nrv)[c[0]])
	{
		c[1] = init_config(*nrv, &c[0]);
		if (c[1])
		{
			if (!make_configs_rdin(nrv, files, &heredoc, &c[0]))
			{
				if (!ft_strncmp(*nrv[c[0]], "<<", ft_strlen(*nrv[c[0]])))
					return (exit_readin(files, heredoc, 666));
				return (exit_readin(files, heredoc, -1));
			}
			(*nrv) = get_newargv_rdin((*nrv), c[0], paths);
			if (!(*nrv))
				return (exit_readin(files, heredoc, 1));
		}
	}
	return (dup_readin(&files, &heredoc, c[2]));
}

char	**init_files(char **newargv, int *c2)
{
	char	**files;
	int		n_files;
	int		c;

	c2[0] = 0;
	c2[2] = 0;
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
