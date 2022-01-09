/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:23:30 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/09 19:38:45 by edjavid          ###   ########.fr       */
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
	if (arr_str[i] == NULL)
		return ;
	while (arr_str[++i])
	{
		new_str = ft_get_dollar_var(arr_str[i], list);
		free(arr_str[i]);
		arr_str[i] = ft_strdup(new_str);
		if (new_str)
			free(new_str);
	}
}

int	ft_assign(t_element *tmp, t_control *list, char *retreat, int i)
{
	t_element	*new;
	char		*nodq;

	tmp = list->first_env_var;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(*new));
	if (!new)
		return (FAILURE);
	nodq = ft_strdup(retreat);
	new->str = ft_remove_quotes(nodq);
	free(nodq);
	new->var_name = add_var_name(new->str);
	new->next = NULL;
	new->index = i;
	tmp->next = new;
	return (SUCCESS);
}

/* check if there are bad entries */
int	process_retreat(char *newargv, char *retreat)
{
	if (retreat == NULL)
		return (FAILURE);
	if (!newargv[0] || (newargv[0] == '=') || ((retreat[0] <= '9')
			&& (retreat[0] >= '0')))
	{
		ft_printf_fd(1, "Minishell: export: \'%s\' : not a valid identifier\n",
			retreat);
		return (FAILURE);
	}
	return (SUCCESS);
}
