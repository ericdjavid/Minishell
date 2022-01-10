/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:26:57 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/10 13:28:34 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_both(t_control *list, char *old_path, char *pwd, int ret)
{
	char	*cur;

	cur = get_absolute_path();
	if (!cur)
		return (0);
	if (ret == 2)
	{
		if (!ft_modify_pwd(list, old_path, "PWD", 666))
			return (free_cur(cur));
		if (!ft_modify_pwd(list, pwd, "OLDPWD", 1))
			return (free_cur(cur));
	}
	else
	{
		if (!ft_modify_pwd(list, cur, "PWD", 666))
			return (free_cur(cur));
		if (!ft_modify_pwd(list, pwd, "OLDPWD", 1))
			return (free_cur(cur));
	}
	free(cur);
	return (1);
}

int	ft_modify_pwd(t_control *list, char *path, char *pwd, int type)
{
	char	*str;
	char	*joined;

	str = ft_strdup(pwd);
	if (!str)
		return (0);
	if (type == 1)
		joined = ft_strjoin2("OLDPWD=", path);
	else
		joined = ft_strjoin2("PWD=", path);
	if (joined && elem_in_list(list->first_export, str))
	{
		mdval(elem_in_list(list->first_export, str), joined, DEAL_EXPORT);
		mdval(elem_in_list(list->first_env, str), joined, DEAL_ENV);
	}
	if (joined)
		free(joined);
	free(str);
	return (1);
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

char	*alloc_values(char *path, t_control *list, int type)
{
	t_element	*elm;
	char		*str;

	elm = elem_in_list(list->first_env, path);
	if (type == 1)
	{
		if (!elm)
		{
			str = get_absolute_path();
			if (!str)
				return (0);
		}
		else
			str = get_var_value(elm->str);
	}
	else if (elm)
		str = get_var_value(elm->str);
	else
	{
		str = malloc(1);
		if (!str)
			return (0);
		*str = 0;
	}
	return (str);
}

void	deal_old_path(int *ret, char *old_path)
{
	if (*old_path)
		*ret = chdir(old_path);
	else
		*ret = 1;
	if (!*ret)
	{
		*ret = 2;
		ft_printf_fd(1, "%s\n", old_path);
	}
	else if (*ret == 1)
		ft_printf_fd(2,
			"minishell: cd: OLDPWD not set\n");
	else
		ft_printf_fd(2,
			"minishell: cd: %s: No such file or directory\n",
			old_path);
}
