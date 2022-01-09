/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:18:13 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/06 16:38:36 by abrun            ###   ########.fr       */
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
	if (!tmp)
		return (NULL);
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

	new_str = ++str;
	tmp = first;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_name, new_str, ft_strlen(new_str)) == 0)
			return (ft_get_good_str(tmp->str));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

t_element	*elem_in_list(t_element *first, char *str)
{
	t_element	*tmp;
	char		*new_str;

	new_str = str;
	tmp = first;
	while (tmp)
	{
		if (ft_strncmp(tmp->var_name, new_str, ft_strlen(tmp->var_name)) == 0)
			return (tmp);
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
