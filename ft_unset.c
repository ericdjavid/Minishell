/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:17:25 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/10 14:59:52 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_stuff(t_element *first, char *str)
{
	t_element	*tmp;
	int			i;

	if (!first)
	{
		printf("list is empty !\n");
		return (FAILURE);
	}
	tmp = first;
	i = 0;
	printf(YELLOW"---LIST %s---\n", str);
	while (tmp != NULL)
	{
		printf("[%s]\n", tmp->str);
		tmp = tmp->next;
		i++;
	}
	printf("----------\n" END);
	return (1);
}

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
		printf("we are comparing |%s| |%s|\n", tmp->var_name, str);
		if (ft_strncmp(tmp->var_name, str, ft_strlen(tmp->var_name)) == 0)
		{
			printf("is in the fucking list\n");
			if (tmp == first)
			{
				printf("it's the first elem\n");
				if (tmp->next)
				{
					printf("next is true first to be free and 2 to be 1\n");
					tmp2 = first->next;
					free(first->str);
					free(first->var_name);
					free(first);
					first = tmp2;
					return ;
				}
				else
				{
					//OKKKKK
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
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

void	ft_delete_from_lists(t_control *control, char *str)
{
	ft_print_stuff(control->first_env_var, "env var list");
	ft_delete_in_list(control->first_env_var, str);
	// ft_delete_in_list(control->first_export, str);
	// ft_delete_in_list(control->first_env, str);
}

void ft_delete(t_control *control, char *str, int type)
{
	t_element *tmp;
	t_element *tmp2;

(void)str;
	if (type == NEO_ENV)
		tmp = control->first_env_var;
	if (type == DEAL_ENV)
		tmp = control->first_env_var;
	if (type == DEAL_EXPORT)
		tmp = control->first_export;
	tmp2 = tmp;
	while (tmp && tmp->var_name)
	{
		if (ft_strncmp(str, tmp->var_name,
			ft_strlen(tmp->var_name)) == 0)
		{
			printf("is in the fucking list\n");
			if (tmp2 == tmp)
			{
				printf("it is the first element of the list\n");
				tmp = tmp->next;
				free(tmp2->str);
				free(tmp2->var_name);
				free(tmp2);
				break ;
			}
		}
		if (tmp->next == NULL)/* code */
			break ;
		tmp = tmp->next;
	}
}

t_element *ft_good_find_in_list(t_element *first, char *noequal_str)
{
	t_element *tmp;

	tmp = first;

	while (tmp && tmp->var_name)
	{
		if (ft_strncmp(tmp->var_name, noequal_str,
			ft_strlen(noequal_str)) == 0)
		{
			printf(RED"it's in the fucking list\n"END);
			return (tmp);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

//if = in uset word, print "not a valid identifier"
int	ft_unset(t_control *control, char **newargv)
{
	char		*noquote_str;
	char		*noequal_str;
	t_element	*tmp;
	int			i;

	i = 0;
	ft_print_stuff(control->first_env_var, "env var");
	while (newargv[++i])
	{
		noquote_str = ft_remove_quotes(newargv[i]);
		noequal_str = ft_get_parsed_env(noquote_str);

		printf("new str is %s\n", noequal_str);
		tmp = ft_good_find_in_list(control->first_env_var, noequal_str);
		if (tmp)
		{
			printf(RED "is in list!\n"END);
			ft_delete(control, noequal_str, NEO_ENV);
			// free(tmp);
			free(noequal_str);
		}
		//if found in export list...
		ft_print_stuff(control->first_env_var, "env var");
	}
	return (1);
}
/*
0    All name operands were successfully unset.
>0    At least one name could not be unset.
*/
