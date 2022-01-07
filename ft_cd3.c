/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:24:56 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/07 17:26:50 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd3(char **newargv, char *old_path, int *ret, t_control *list)
{
	if (ft_matlen(newargv) > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		free(old_path);
		return (1);
	}
	else if (ft_matlen(newargv) > 1 && newargv[1][0] == '-' && !newargv[1][1])
		deal_old_path(ret, old_path);
	else
		*ret = ft_cd_2(newargv, list);
	if (!*ret)
		modify_both(list, old_path);
	else
	{
		free(old_path);
		g_status = 42;
		return (3);
	}
	return (666);
}
