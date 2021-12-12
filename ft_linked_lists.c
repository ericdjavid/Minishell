/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:18:13 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/12 17:05:08 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_good_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (*str != '\0' && *str != '=')
	{
		str++;
		i++;
	}
	if (*str == '=')
		str++;
	if (*str == '\0')
		return (NULL);
	return (str);
}

char	*ft_get_parsed_env(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (str);
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	if (str)
		free(str);
	return (tmp);
}

char	*is_in_list(t_element *first, char *str)
{
	t_element	*tmp;
	char		*new_str;
	// char		*wip_str;

	new_str = ++str;
	tmp = first;
	while (tmp)
	{
		// wip_str = ft_get_parsed_env(tmp->str);
		// printf("wip str is %s\n", wip_str);
		// printf("think I got the var names.. : %s\n", tmp->var_name);
		if (ft_strncmp(tmp->var_name, new_str, ft_strlen(new_str)) == 0)
		{
		// printf("we found the same\n");
		// 	free(wip_str);
			return (ft_get_good_str(tmp->str));
		}
		// else
		// 	free(wip_str);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_index(t_element *elem)
{
	int	i;

	i = 0;
	while (elem->next)
	{
		elem->index = ++i;
		elem = elem->next;
	}
	elem->index = ++i;
	return ;
}

// TO DEAL WITH EXPORT QUOTES
	// 1 REPLACE EXISTING SIMPLE QUOTES BY DOUBLE
	// 2 ADD DOUBLE QUOTES TO ALL
	//(if new env var with simple quotes, replace by double quotes)
// char	*processing_exp(char *str)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=' && str[i + 1] == "\'")
// 		{

// 		}
// 		i++;
// 	}
// }

int	ft_init_list(t_control *list, char **envp)
{
	int			i;
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
	i = -1;
	while (envp[++i])
	{
		list->size++;
		add_end_list(envp[i], list->first_export, 0, list);
		add_end_list(envp[i], list->first_env, 0, list);
	}
	add_index(list->first_export);
	while (check_order(list) == FALSE)
		order_ascii(list);
	return (SUCCESS);
}
