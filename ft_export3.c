/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:23:30 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/27 16:24:53 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_element *first, t_bool bool)
{
	t_element	*tmp;

	tmp = first;
	if (!first)
		return ;
	while (tmp)
	{
		if (bool == TRUE)
			ft_printf_fd(1, "declare -x ");
		ft_printf_fd(1, "%s\n", tmp->str);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return ;
}

void	ft_process_str(char **arr_str, t_control *list, char *new_str)
{
	int	i;

	i = 0;
	while (arr_str[++i])
	{
		new_str = ft_get_dollar_var(arr_str[i], list);
		free(arr_str[i]);
		arr_str[i] = ft_strdup(new_str);
		if (new_str)
			free(new_str);
	}
}

char	*ft_deal_dollar(char *str, t_control *list)
{
	char	*new_str;
	char	**arr_str;
	char	*ret;
	char	*ret2;
	int		i;

	new_str = NULL;
	if (!(ft_strchr(str, '$')))
		return (NULL);
	arr_str = ft_split(str, "$");
	if (!arr_str)
		return (NULL);
	ft_process_str(arr_str, list, new_str);
	i = 0;
	ret = NULL;
	while (arr_str[++i])
		ret = ft_strjoin(ret, arr_str[i]);
	free_matc(arr_str);
	ret2 = ft_remove_quotes(ret);
	free(ret);
	return (ret2);
}

int	ft_assign(t_element *tmp, t_control *list, char *retreat, int i)
{
	t_element	*new;

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
	return (SUCCESS);
}

int	process_retreat(char *newargv, char *retreat)
{
	if (!(ft_check_position('$', '=', newargv)) || (newargv[0] <= 'Z'
			&& newargv[0] >= 'A') || (newargv[0] == '='
			|| ((retreat[0] <= '9') && (retreat[0] >= '0'))))
	{
		ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
		return (FAILURE);
	}
	return (SUCCESS);
}
