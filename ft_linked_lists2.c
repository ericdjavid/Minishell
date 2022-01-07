/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:14:53 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/07 18:37:51 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_deal_shlvl(t_control *control)
{
	t_element	*tmp;
	char		*c;

	tmp = ft_good_find_in_list(control->first_env, "SHLVL");
	if (!tmp)
		return ;
	c = ft_get_good_str(tmp->str);
	c[0] = c[0] + 1;
	tmp = ft_good_find_in_list(control->first_export, "SHLVL");
	if (!tmp)
		return ;
	c = ft_get_good_str(tmp->str);
	c[1] = c[1] + 1;
}

t_element	*ft_init(void)
{
	t_element	*first;

	first = malloc(sizeof(*first));
	if (!first)
		return (NULL);
	first->str = NULL;
	first->var_name = NULL;
	first->next = NULL;
	first->index = 0;
	return (first);
}

void	ft_init_list2(t_control *list, char **envp)
{
	int			i;

	i = -1;
	while (envp[++i])
	{
		list->size++;
		add_end_list(envp[i], list->first_export, DEAL_EXPORT);
		add_end_list(envp[i], list->first_env, 0);
	}
	ft_deal_shlvl(list);
	add_index(list->first_export);
	while (check_order(list) == FALSE)
		order_ascii(list);
}

int	ft_init_list(t_control *list, char **envp)
{
	t_element	*first_env;
	t_element	*first_export;
	t_element	*first_env_var;

	first_env = ft_init();
	first_export = ft_init();
	first_env_var = ft_init();
	if ((!first_export) || (!first_env) || (!first_env_var))
		return (FAILURE);
	list->first_env = first_env;
	list->first_export = first_export;
	list->first_env_var = first_env_var;
	list->size = 0;
	ft_init_list2(list, envp);
	return (SUCCESS);
}
