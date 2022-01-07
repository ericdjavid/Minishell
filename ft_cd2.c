/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:26:57 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/07 16:27:13 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_both(t_control *list, char *old_path)
{
	ft_modify_pwd(list, old_path, "OLDPWD", 1);
	ft_modify_pwd(list, get_absolute_path(), "PWD", 666);
}

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

char	*alloc_values(char *path, t_control *list, int type)
{
	t_element	*elm;
	char		*str;

	elm = elem_in_list(list->first_env, path);
	if (type == 1)
	{
		if (!elm)
			str = get_absolute_path();
		else
			str = get_var_value(elm->str);
	}
	else
		str = get_var_value(elm->str);
	return (str);
}

void	deal_old_path(int *ret, char *old_path)
{
	*ret = chdir(old_path);
	if (!ret)
		ft_printf_fd(1, "%s\n", old_path);
	else
		ft_printf_fd(2,
			"minishell: cd: %s: No such file or directory\n",
			old_path);
}
