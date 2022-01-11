/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:24:56 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/10 13:28:03 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **newargv, t_control *list)
{
	char	*old_path;
	int		ret;
	int		ret2;

	old_path = alloc_values("OLDPWD", list, 0);
	if (!old_path)
		return (-1);
	ret2 = ft_cd3(newargv, old_path, &ret, list);
	free(old_path);
	return (ret2);
}

void	error_with_file_or_directory(int config, char *home, char *newargv)
{
	if (config == 1)
		ft_printf_fd(2,
			"minishell: cd: %s: No such file or directory\n",
			home);
	else
		ft_printf_fd(2,
			"minishell: cd: %s: No such file or directory\n",
			newargv);
	g_status = 1;
}

int	ft_cd_alone(t_control *list, char **home, int *ret)
{
	t_element		*elm;

	elm = elem_in_list(list->first_env, "HOME");
	if (!elm)
	{
		ft_printf_fd(2, "minishell: cd: HOME not set\n");
		return (0);
	}
	*home = get_var_value(elm->str);
	if (!*home)
		*ret = 1;
	*ret = chdir(*home);
	return (1);
}

int	ft_cd_2(char **newargv, t_control *list)
{
	char	*home;
	int		config;
	int		ret;

	home = NULL;
	if (ft_matlen(newargv) == 1)
	{
		config = ft_cd_alone(list, &home, &ret);
		if (!config)
			return (1);
	}
	else
	{
		config = 2;
		ret = chdir(newargv[1]);
	}
	if (ret)
		error_with_file_or_directory(config, home, newargv[1]);
	if (home)
		free(home);
	return (ret);
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
