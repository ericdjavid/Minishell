/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:42:20 by abrun             #+#    #+#             */
/*   Updated: 2021/11/21 16:54:19 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO: fix the SIGSEV when pressing ENTER
int	ft_builtins(char **newargv, t_control *list)
{
	if (!ft_strncmp(newargv[0], "echo", ft_strlen(newargv[0])))
		return (ft_echo(newargv));
	else if (!ft_strncmp(newargv[0], "pwd", ft_strlen(newargv[0])))
		return (ft_pwd(newargv));
	else if (!ft_strncmp(newargv[0], "cd", ft_strlen(newargv[0])))
		return (ft_cd(newargv));
	else if (!ft_strncmp(newargv[0], "export", ft_strlen(newargv[0])))
		return (ft_export(list));
	else if (!ft_strncmp(newargv[0], "env", ft_strlen(newargv[0])))
		return (ft_env(list));
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
