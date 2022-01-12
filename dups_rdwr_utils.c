/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_rdwr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:35:13 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 18:35:32 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_inout(int config)
{
	if (config >= 3)
		return (1);
	return (0);
}

int	is_other_rdwr(int inout, t_file *files)
{
	files = files->next;
	while (files)
	{
		if (inout && files->config >= 3)
			return (1);
		if (!inout && files->config <= 2)
			return (1);
		files = files->next;
	}
	return (0);
}
