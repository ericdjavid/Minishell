/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:31:10 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/04 14:18:18 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_last(t_element *first)
{
	t_element	*tmp;

	tmp = first;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next->str);
	free(tmp->next->var_name);
	free(tmp->next);
	tmp->next = NULL;
	return ;
}

int	ft_is_space_before_qual(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_deal_space(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	split = ft_split(str, " ");
	while (split[i])
		i++;
	free_matc(split);
	return (str);
}

char	*ft_get_dollar_var(char *str, t_control *list)
{
	t_element	*tmp;
	char		*tmp_char;
	char		*deal_space;

	tmp_char = NULL;
	deal_space = NULL;
	if (ft_strchr(str, ' '))
		deal_space = ft_deal_space(str);
	tmp = ft_is_in_list(list, str);
	if (!tmp || !tmp->str)
		return (NULL);
	free(tmp_char);
	tmp_char = NULL;
	tmp_char = add_value_name(tmp->str);
	return (tmp_char);
}

t_bool	is_surrounded(char *str, size_t size, char c)
{
	if (str[0] == c && str[size] == c)
		return (TRUE);
	return (FALSE);
}
