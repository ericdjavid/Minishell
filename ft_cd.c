/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:39:49 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 15:18:46 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **newargv)
{
	int			ret;
	static char	*old_path = NULL;

	if (!old_path)
		old_path = get_absolutePath();
	if (newargv[1][0] == '-' && !newargv[1][1])
	{
		ret = chdir(old_path);
		write(1, old_path, ft_strlen(old_path));
		write(1, "\n", 1);
	}
	else
	{
		free(old_path);
		old_path = get_absolutePath();
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
			status = 1;
		}
	}
	return (1);
}

char	*get_absolutePath(void)
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
