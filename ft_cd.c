/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:39:49 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 13:12:38 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_modify_pwd(t_control *list, char *path, char *pwd, int type)
{
	char	*str;
	char	*joined;

	str = ft_strdup(pwd);
	if (type == 1)
		joined = ft_strjoin2("OLDPWD=", path);
	else
		joined = ft_strjoin2("PWD=", path);
	if (elem_in_list(list->first_export, str))
	{
		mdval(elem_in_list(list->first_export, str), joined, DEAL_EXPORT);
		mdval(elem_in_list(list->first_env, str), joined, DEAL_ENV);
	}
	if (type != 1)
		free(path);
	free(joined);
	free(str);
}

int	ft_cd(char **newargv, t_control *list)
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
		ft_printf_fd(1, "%s\n", old_path);
	}
	else
	{
		old_path = ft_cd_2(newargv, ret, old_path);
		if (!old_path)
			return (-1);
	}
	ft_modify_pwd(list, old_path, "OLDPWD", 1);
	ft_modify_pwd(list, get_absolute_path(), "PWD", 666);
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
