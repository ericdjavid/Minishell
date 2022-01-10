/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:24:56 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/10 13:27:17 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd3(char **newargv, char *old_path, int *ret, t_control *list)
{
	char	*pwd;
	int		ret2;

	ret2 = 1;
	pwd = alloc_values("PWD", list, 1);
	if (!pwd)
		return (0);
	if (ft_matlen(newargv) > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else if (ft_matlen(newargv) > 1 && newargv[1][0] == '-' && !newargv[1][1])
		deal_old_path(ret, old_path);
	else
		*ret = ft_cd_2(newargv, list);
	if (!*ret || *ret == 2)
		ret2 = modify_both(list, old_path, pwd, *ret);
	else if (*ret != -1)
		g_status = 42;
	free(pwd);
	return (ret2);
}

int	free_cur(char *cur)
{
	free(cur);
	return (0);
}
