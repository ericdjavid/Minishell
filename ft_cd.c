/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:39:49 by abrun             #+#    #+#             */
/*   Updated: 2021/12/28 14:15:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **newargv)
{
	int			ret;
	static char	*old_path = NULL;

	ret = 0;
	if (!old_path)
		old_path = get_absolute_path();
	if (ft_matlen(newargv) > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else if (ft_matlen(newargv) > 1 && newargv[1][0] == '-' && !newargv[1][1])
	{
		ret = chdir(old_path);
		write(1, old_path, ft_strlen(old_path));
		write(1, "\n", 1);
	}
	else
	{
		old_path = ft_cd_2(newargv, ret, old_path);
		if (!old_path)
			return (-1);
	}
	return (1);
}

char	*ft_cd_2(char **newargv, int ret, char *old_path)
{
	free(old_path);
	old_path = get_absolute_path();
	if (!old_path)
		return (0);
	if (ft_matlen(newargv) == 1)
		ret = chdir(getenv("HOME"));
	else if (newargv[1][0] != '~')
		ret = chdir(newargv[1]);
	else
	{
		chdir(getenv("HOME"));
		newargv[1] += 2;
		ret = chdir(newargv[1]);
		newargv[1] -= 2;
	}
	// TODO: changer la valeur de la variable PWD et OLDPWD de env
	if (ret)
	{
		ft_printf_fd(2,
			"minishell: cd: %s: No such file or directory\n",
			newargv[1]);
		g_status = 1;
	}
	return (old_path);
}

char	*get_absolute_path(void)
{
	char	buf[4096];
	char	*path;
	int		c;
	int		c_2;

	c = 0;
	while (!getcwd(buf, c))
		c++;
	path = malloc(c + 1);
	if (!path)
		return (0);
	c_2 = -1;
	while (++c_2 < c)
		path[c_2] = buf[c_2];
	path[c_2] = 0;
	return (path);
}
