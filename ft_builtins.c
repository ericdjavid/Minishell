/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:42:20 by abrun             #+#    #+#             */
/*   Updated: 2021/11/28 15:56:57 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtins(char **newargv, t_control *list)
{
	size_t	len_0;

	len_0 = ft_strlen(newargv[0]);
	if (!ft_strncmp(newargv[0], "echo", len_0))
		return (ft_echo(newargv));
	else if (!ft_strncmp(newargv[0], "pwd", len_0))
		return (ft_pwd(newargv));
	else if (!ft_strncmp(newargv[0], "cd", len_0))
		return (ft_cd(newargv));
	else if (!ft_strncmp(newargv[0], "export", len_0))
		return (ft_export(list, newargv));
	else if (!ft_strncmp(newargv[0], "env", len_0))
		return (ft_env(list));
	else if (ft_matlen(newargv) == 1
			&& !ft_strncmp(newargv[0], "exit", len_0))
		return (1);
	return (0);
}

int	is_builtins(char *newargv)
{
	if (!ft_strncmp(newargv, "echo", ft_strlen(newargv)))
		return (1);
	else if (!ft_strncmp(newargv, "pwd", ft_strlen(newargv)))
		return (1);
	else if (!ft_strncmp(newargv, "cd", ft_strlen(newargv)))
		return (1);
	else if (!ft_strncmp(newargv, "export", ft_strlen(newargv)))
		return (1);
	else if (!ft_strncmp(newargv, "env", ft_strlen(newargv)))
		return (1);
	return (0);
}
