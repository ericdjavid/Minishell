/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_rdwr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:19:39 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 18:36:50 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_manage_rdwr(char ***newargv, int forked)
{
	t_file	*files;
	int		c;
	int		*ret;
	int		config;

	files = NULL;
	ret = init_ret2();
	if (!ret)
		return (malloc_failed());
	c = 0;
	while ((*newargv)[c])
	{
		config = get_config((*newargv)[c]);
		if (config)
		{
			if (!add_file((*newargv)[c + 1], config, &files))
				return (exit_manage_rdwr(ret, files));
			(*newargv) = get_newargv_rdwr(*newargv, c);
			if (!(*newargv))
				return (exit_manage_rdwr(ret, files));
		}
		else
			c++;
	}
	return (make_dups_rdwr(files, ret, forked, (*newargv)[0]));
}

int	*init_ret2(void)
{
	int	*ret;

	ret = malloc(sizeof(int) * 3);
	if (!ret)
		return (malloc_failed());
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	return (ret);
}

int	add_file(char *file, int config, t_file **files)
{
	t_file	*new;

	new = ft_filenew(file, config);
	if (!new)
		return (0);
	if (config == 1)
		new->heredoc = get_heredoc(file);
	ft_fileadd_back(files, new);
	return (1);
}

char	**get_newargv_rdwr(char **old, int c)
{
	char	**new;
	int		c_2;
	int		i;

	new = malloc(sizeof(char *) * (ft_matlen(old) - 1));
	if (!new)
		return (exit_get_newrdwr(old, new));
	c_2 = 0;
	i = 0;
	while (old[c_2 + i])
	{
		if (i || c_2 != c)
		{
			new[c_2] = ft_strdup(old[c_2 + i]);
			if (!new[c_2])
				return (exit_get_newrdwr(old, new));
			c_2++;
		}
		else
			i = 2;
	}
	new[c_2] = 0;
	free_matc(old);
	return (new);
}

int	get_config(char *s)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!ft_strncmp(s, "<<", s_len))
		return (1);
	if (!ft_strncmp(s, "<", s_len))
		return (2);
	if (!ft_strncmp(s, ">", s_len))
		return (3);
	else if (!ft_strncmp(s, ">>", s_len))
		return (4);
	return (0);
}
