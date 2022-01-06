/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:55:12 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 12:03:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_new_redir(char **newargv, int redir)
{
	char	**new;
	int		c;
	int		c_2;

	new = malloc(sizeof(char *) * ft_matlen(newargv));
	new = 0;
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

int	*assign_config(int *box, int config, int fd)
{
	if (config == 3)
		box[1] = 1;
	if (config == 4)
		box[2] = 1;
	box[3] = fd;
	return (box);
}

int	*exit_redirection(int *box, int *ret)
{
	int	c;
	int	value;

	c = 0;
	value = 0;
	while (c < 2)
	{
		value += box[c];
		c++;
	}
	ret[1] = value + 1;
	if (box[3])
		ret[2] = box[3];
	else
		ret[2] = 1;
	free(box);
	return (ret);
}

int	is_other_redin(char **newargv)
{
	int	c;

	c = 0;
	while (newargv[c])
	{
		if (!ft_strncmp(newargv[c], "<", ft_strlen(newargv[c])))
			return (1);
		c++;
	}
	return (0);
}
