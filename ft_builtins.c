/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:42:20 by abrun             #+#    #+#             */
/*   Updated: 2021/12/10 15:56:06 by abrun            ###   ########.fr       */
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
	{
		if (!newargv[1])
			return (ft_export(list, newargv));
		else
			return (1);
	}
	else if (!ft_strncmp(newargv[0], "env", len_0))
		return (ft_env(list));
	else if (ft_matlen(newargv) == 1
		&& !ft_strncmp(newargv[0], "exit", len_0))
		return (1);
	else if (!ft_strncmp(newargv[0], "unset", len_0))
		return (1);
	if (!ft_strncmp(newargv[0], "/usr/bin/clear", len_0))
		return (ft_clear(newargv));
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
	else if (!ft_strncmp(newargv, "unset", ft_strlen(newargv)))
		return (1);
	return (0);
}
