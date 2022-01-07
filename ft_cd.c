/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:39:49 by abrun             #+#    #+#             */
/*   Updated: 2022/01/07 16:00:17 by abrun            ###   ########.fr       */
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

char	*get_var_value(char *var_val)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!var_val)
		return (NULL);
	while (var_val[++i])
	{
		if (var_val[i] == '=')
			break ;
	}
	str = malloc(sizeof(char) * (ft_strlen(var_val) - i + 1));
	if (!str)
		return (NULL);
	while (var_val[++i])
	{
		str[++j] = var_val[i];
	}
	str[++j] = '\0';
	return (str);
}

int	ft_cd(char **newargv, t_control *list)
{
	char		*old_path;
	t_element	*elm;
	int			ret;
	char		*pwd;

	elm = elem_in_list(list->first_env, "OLDPWD");
	if (!elm)
		return (0);
	old_path = get_var_value(elm->str);
	elm = elem_in_list(list->first_env, "PWD");
	if (!elm)
		pwd = get_absolute_path();
	else
		pwd = get_var_value(elm->str);
	if (!old_path)
	{
		old_path = get_absolute_path();
		if (!old_path)
			return (-1);
	}
	if (ft_matlen(newargv) > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		free(old_path);
		return (1);
	}
	else if (ft_matlen(newargv) > 1 && newargv[1][0] == '-' && !newargv[1][1])
	{
		ret = chdir(old_path);
		if (!ret)
			ft_printf_fd(1, "%s\n", old_path);
		else
			ft_printf_fd(2,
				"minishell: cd: %s: No such file or directory\n",
				old_path);
	}
	else
	{
		ft_cd_2(newargv, list, &ret);
	}
	if (!ret)
	{
		ft_modify_pwd(list, old_path, "OLDPWD", 1);
		ft_modify_pwd(list, get_absolute_path(), "PWD", 666);
	}
	free(old_path);
	free(pwd);
	return (1);
}

void	ft_cd_2(char **newargv, t_control *list, int *ret)
{
	char		*home;
	t_element		*elm;
	int		config;

	home = NULL;
	if (ft_matlen(newargv) == 1)
	{
		config = 1;
		elm = elem_in_list(list->first_env, "HOME");
		if (!elm)
		{
			ft_printf_fd(2, "minishell: cd: HOME not set\n");
			return ;
		}
		home = get_var_value(elm->str);
		*ret = chdir(home);
	}
	else
	{
		config = 2;
		*ret = chdir(newargv[1]);
	}
	if (*ret)
	{
		if (config == 1)
			ft_printf_fd(2,
				"minishell: cd: %s: No such file or directory\n",
				home);
		else
			ft_printf_fd(2,
				"minishell: cd: %s: No such file or directory\n",
				newargv[1]);
		g_status = 1;
	}
	if (home)
		free(home);
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
