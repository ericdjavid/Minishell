/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:00:43 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 14:41:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*ft_filenew(char *name, int config)
{
	t_file		*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (0);
	new->config = config;
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (0);
	}
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}

void	ft_clearfiles(t_file **files)
{
	t_file	*next;

	while (*files)
	{
		next = (*files)->next;
		if ((*files)->config == 1 && (*files)->heredoc)
			free((*files)->heredoc);
		free((*files)->name);
		free(*files);
		*files = next;
	}
	free(*files);
}

void	ft_fileadd_back(t_file **files, t_file *new)
{
	t_file		*last;

	last = ft_filelast(*files);
	if (last)
		last->next = new;
	else
		*files = new;
}

t_file	*ft_filelast(t_file *files)
{
	t_file	*next;

	if (files == NULL)
		return (0);
	next = files->next;
	while (next)
	{
		files = next;
		next = files->next;
	}
	return (files);
}

int	ft_filesize(t_file *files)
{
	int	lenght;

	lenght = 0;
	while (files)
	{
		lenght++;
		files = files->next;
	}
	return (lenght);
}
