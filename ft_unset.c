/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:17:25 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/09 11:23:56 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_str(t_element *tmp)
{
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		free(tmp->str);
		free(tmp->var_name);
		tmp->str = ft_strdup(tmp->next->str);
		tmp->var_name = ft_strdup(tmp->next->var_name);
		tmp = tmp->next;
	}
	if (tmp->str)
		free(tmp->str);
	if (tmp->var_name)
		free(tmp->var_name);
	free(tmp);
	tmp = NULL;
	return ;
}

void	ft_delete_in_list(t_element *first, char *str)
{
	t_element	*tmp;
	t_element	*tmp2;

	tmp = first;
	if (tmp == NULL || tmp->str == NULL )
	{
		printf(YELLOW "returning null\n"END);
		return ;
	}
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		printf("we are comparing |%s| |%s|\n", tmp->var_name, str);
		if (ft_strncmp(tmp->var_name, str, ft_strlen(tmp->var_name)) == 0)
		{
			printf("is in the fucking list\n");
			if (tmp == first)
			{
				printf("is first elem\n");
				if (tmp->next)
				{
					// not working =()
					tmp2 = first->next;
					free(first->str);
					free(first->var_name);
					free(first);
					first = tmp2;
					return ;
				}
				else
				{
					printf("next is null so first should be null\n");
					first->str = NULL;
					first->var_name = NULL;
					first = NULL;
					return ;
				}
			}
			else if (tmp->next == NULL)
			{
				printf(RED"is last elem of list\n"END);
				free(tmp->str);
				free(tmp->var_name);
				tmp = NULL;
				break ;
			}
			else
				ft_replace_str(tmp);
		}
		tmp = tmp->next;
	}
}

void	ft_delete_from_lists(t_control *control, char *str)
{
	ft_delete_in_list(control->first_env_var, str);
	// ft_delete_in_list(control->first_export, str);
	ft_delete_in_list(control->first_env, str);
}

//if = in uset word, print "not a valid identifier"
int	ft_unset(t_control *control, char **newargv)
{
	char		*neo_str;
	t_element	*tmp;
	int			i;

	i = 0;
	while (newargv[++i])
	{
		neo_str = ft_remove_quotes(newargv[i]);
		tmp = ft_is_in_list(control, neo_str);
		if (tmp)
		{
			printf(RED "is in list!\n"END);
			ft_delete_from_lists(control, neo_str);
			// free(tmp);
			free(neo_str);
		}
	}
	return (1);
}
/*
0    All name operands were successfully unset.
>0    At least one name could not be unset.
*/
