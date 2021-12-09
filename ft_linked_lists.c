/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:18:13 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/09 20:49:18 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_good_str(char *str)
{
	int	i;

	i = 0;
	while (*str != '=' && *str != '\0')
	{
		str++;
		i++;
	}
	if (*str == '=')
		str++;
	if (*str == '\0')
		return (NULL);
	// printf("new str is |%s|", str);
	return (str);
}

char	*ft_get_parsed_env(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*is_in_list(t_element *first, char *str)
{
	t_element	*tmp;
	char		*new_str;
	char		*wip_str;

	new_str = ++str;
	tmp = first;
	while (tmp)
	{
		wip_str = ft_get_parsed_env(tmp->str);
		if (ft_strncmp(wip_str, new_str, ft_strlen(wip_str)) == 0)
		{
			free(wip_str);
			return (ft_get_good_str(tmp->str));
		}
		else
			free(wip_str);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
	}
	return (FALSE);
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
	list->size_env = 0;
	i = -1;
	while (envp[++i])
	{
		list->size++;
		add_end_list(envp[i], list->first_export, 0);
		add_end_list(envp[i], list->first_env, 0);
	}
	add_index(list->first_export);
	while (check_order(list) == FALSE)
		order_ascii(list);
	return (SUCCESS);
}
