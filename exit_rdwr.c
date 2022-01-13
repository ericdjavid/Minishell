/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_rdwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:31:32 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 18:41:57 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*exit_dups_rdwr(int *ret, t_file *files)
{
	free(ret);
	ft_clearfiles(&files);
	return (0);
}

char	**exit_get_newrdwr(char **old, char **new)
{
	if (new)
		free_matc(new);
	free_matc(old);
	return (0);
}

int	*exit_manage_rdwr(int *ret, t_file *files)
{
	free(ret);
	ft_clearfiles(&files);
	return (malloc_failed());
}

int	*malloc_failed(void)
{
	g_status = 42;
	return (0);
}
