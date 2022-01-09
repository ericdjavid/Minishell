/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_newargv_rdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:33:20 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 16:43:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_newargv_rdin(char **newargv, int c, char **paths)
{
	char	**new;
	int		counter[3];

	new = malloc(sizeof(char *) *(ft_matlen(newargv) - 1));
	if (!new)
	{
		free_matc(newargv);
		return (0);
	}
	counter[0] = c;
	counter[1] = 0;
	counter[2] = 0;
	while (newargv[counter[1]])
	{
		if (counter[1] == counter[0])
			counter[1] += 2;
		if (newargv[counter[1]])
			new = add_one_arg_rdin(newargv, new, paths, &counter[0]);
	}
	new[counter[2]] = 0;
	free_matc(newargv);
	return (new);
}

char	**add_one_arg_rdin(char **newargv, char **new,
		char **paths, int *counter)
{
	new[counter[2]] = ft_strdup_rdin(newargv[counter[1]], newargv, new);
	if (!new[counter[2]])
		return (0);
	if (counter[2] == counter[0])
	{
		new[counter[2]] = init_cmd_path(new[counter[2]], paths);
		if (!new[counter[2]])
			return (0);
	}
	counter[1]++;
	counter[2]++;
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
