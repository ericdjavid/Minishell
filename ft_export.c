/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:18:36 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/23 17:34:46 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_var_name(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*str2;
	int		nb;

	i = -1;
	nb = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\"')
			nb++;
	}
	str2 = malloc(sizeof(char) * (ft_strlen(str) - nb + 1));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			continue ;
		str2[j] = str[i];
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

//add the simple quotes before =
//TODO: when creating a new env with " ", bad behavior (double quotes)
char	*add_str2(char *str, int type)
{
	char	*tmp;
	int		i;
	int		j;
	t_bool	is_equal;
	int		k;

	i = 0;
	k = 0;
	is_equal = FALSE;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '=')
			is_equal = TRUE;
		i++;
	}
	if (type == DEAL_ENV && is_equal == FALSE)
		return (NULL);
	if (is_equal == TRUE && type == DEAL_EXPORT)
		tmp = malloc(sizeof(char) * (ft_strlen(str) + 1 + 500));
	if (!tmp)
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (is_equal == TRUE && type == DEAL_EXPORT && str[i] == '=' && k == 0)
		{
			tmp[j] = str[i];
			tmp[++j] = '\"';
			i++;
			j++;
			k = 1;
			continue ;
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	if (is_equal == TRUE && type == DEAL_EXPORT)
	{
		tmp[j] = '\"';
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	add_end_list(char *str, t_element *first, int type)
{
	t_element	*tmp;
	t_element	*tmp2;
	char		*str_new;

	str_new = add_str2(str, type);
	if (!str_new)
		return (FAILURE);
	if (!(first->str))
	{
		first->str = str_new;
		first->var_name = add_var_name(str_new);
		first->next = NULL;
		// first->control = control;
		return (SUCCESS);
	}
	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = malloc(sizeof(*tmp));
	tmp2->str = str_new;
	tmp2->var_name = add_var_name(str_new);
	tmp2->next = NULL;
	tmp2->index = 0;
	// first->control = control;
	tmp->next = tmp2;
	return (SUCCESS);
}

void	ft_print_export(t_element *first, t_bool bool)
{
	t_element	*tmp;

	tmp = first;
	if (!first)
		return ;
	while (tmp)
	{
		if (bool == TRUE)
			ft_printf_fd(1, "export ");
		ft_printf_fd(1, "%s\n", tmp->str);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return ;
}

char	*ft_deal_dollar(char *str, t_control *list)
{
	char	*new_str;
	char	**arr_str;
	char	*ret;
	char	*ret2;
	int		i;

	i = 0;
	if (!(ft_strchr(str, '$')))
		return (NULL);
	arr_str = ft_split(str, "$");
	if (!arr_str)
		return (NULL);
	while (arr_str[++i])
	{
		new_str = ft_get_dollar_var(arr_str[i], list);
		free(arr_str[i]);
		arr_str[i] = ft_strdup(new_str);
		if (new_str)
			free(new_str);
	}
	i = 0;
	ret = NULL;
	while (arr_str[++i])
		ret = ft_strjoin(ret, arr_str[i]);
	free_matc(arr_str);
	ret2 = ft_remove_quotes(ret);
	free(ret);
	return (ret2);
}

int ft_get_new_var(t_control *list, char **newargv)
{
	int			i;
	t_element	*new;
	t_element	*tmp;
	char		*retreat;

	i = 0;
	retreat = NULL;
	while (newargv[++i])
	{
		if (retreat)
			free (retreat);
		retreat = NULL;
		retreat = ft_deal_dollar(newargv[i], list);
		if (retreat == NULL)
			retreat = ft_remove_simple_quotes(newargv[i]);
		if (!(ft_check_position('$', '=', newargv[i])) || (newargv[i][0] <= 'Z'
			&& newargv[i][0] >= 'A') || (newargv[i][0] == '='
			|| ((retreat[0] <= '9') && (retreat[0] >= '0'))))
		{
			ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
			continue ;
		}
		tmp = ft_is_in_list(list, retreat);
		if ((ft_is_space_before_qual(retreat))
			|| (is_quest(retreat) == TRUE))
		{
			ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
			free(tmp);
			continue ;
		}
		if (tmp)
		{
			if (!ft_strchr(retreat, '='))
				continue ;
			free(tmp->str);
			tmp->str = ft_strdup(retreat);
			continue ;
		}
		if (list->first_env_var->str == NULL)
		{
			list->first_env_var->str = ft_strdup(retreat);
			list->first_env_var->var_name
				= add_var_name(list->first_env_var->str);
			continue ;
		}
		tmp = list->first_env_var;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new = malloc(sizeof(*new));
		if (!new)
			return (FAILURE);
		new->str = ft_strdup(retreat);
		new->var_name = add_var_name(new->str);
		new->next = NULL;
		new->index = i;
		tmp->next = new;
	}
	if (retreat)
		free (retreat);
	ft_print_stuff(list->first_env_var, "new env arr");
	ft_add_new_var(list, DEAL_EXPORT);
	ft_print_stuff(list->first_export, "Export list");
	return (1);
}
