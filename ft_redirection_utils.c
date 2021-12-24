/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:55:12 by abrun             #+#    #+#             */
/*   Updated: 2021/12/24 17:55:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_new_redir(char **newargv, int redir)
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
		if (c == redir)
			c += 2;
		if (newargv[c])
		{
			new[c_2] = ft_strdup(newargv[c]);
			if (!new[c_2])
				return (free_redirection(newargv, new));
			c_2++;
			c++;
		}
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

int	*assign_config(int *ret, int config)
{
	if (config == 2)
		ret[0] = 1;
	if (config == 3)
		ret[1] = 1;
	if (config == 4)
		ret[2] = 1;
	return (ret);
}

int	exit_redirection(int *ret)
{
	int	c;
	int	value;

	c = 0;
	value = 0;
	while (c < 3)
	{
		value += (ret[c] * (c + 2));
		c++;
	}
	free(ret);
	if (!value)
		return (1);
	return (value);
}
