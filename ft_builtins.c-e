/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:42:20 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 17:44:33 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtins(char **newargv)
{
	if (!ft_strncmp(newargv[0], "echo", ft_strlen(newargv[0])))
		return (ft_echo(newargv));
	else if (!ft_strncmp(newargv[0], "pwd", ft_strlen(newargv[0])))
		return (ft_pwd(newargv));
	else if (!ft_strncmp(newargv[0], "cd", ft_strlen(newargv[0])))
		return (ft_cd(newargv));
	return (0);
}
