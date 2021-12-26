/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:18:36 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/26 18:40:09 by edjavid          ###   ########.fr       */
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

int	ft_count(char *str, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			nb++;
	}
	return (nb);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*str2;
	int		nb;

	if (!str)
		return (NULL);
	nb = ft_count(str, '\"');
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

int	add_str4(char *str, int type, t_bool is_equal, char *tmp)
{
	int	k;
	int	j;
	int	i;

	j = 0;
	k = 0;
	i = 0;
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
		j++;
		i++;
	}
	return (j);
}

void	add_str3(int type, t_bool is_equal, char *str, char *tmp)
{
	int	j;

	j = add_str4(str, type, is_equal, tmp);
	if (is_equal == TRUE && type == DEAL_EXPORT)
	{
		tmp[j] = '\"';
		j++;
	}
	tmp[j] = '\0';
}

char	*add_str2(char *str, int type)
{
	char	*tmp;
	int		i;
	t_bool	is_equal;

	i = -1;
	is_equal = FALSE;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '=')
			is_equal = TRUE;
	}
	if (type == DEAL_ENV && is_equal == FALSE)
		return (NULL);
	if (is_equal == TRUE && type == DEAL_EXPORT)
		tmp = malloc(sizeof(char) * (ft_strlen(str) + 1 + 500));
	if (!tmp)
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	add_str3(type, is_equal, str, tmp);
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
	tmp->next = tmp2;
	return (SUCCESS);
}
