/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:28:28 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/12 14:11:08 by edjavid          ###   ########.fr       */
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

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*str2;
	int		nb;

	i = -1;
	nb = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\"')
			nb++;
	}
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

//Suppress the double quotes before =
//TODO: when creating a new env with " ", bad behavior (double quotes)
char *add_str2(char *str, int type)
{
	char	*tmp;
	int		i;
	int		j;
	t_bool	is_equal;

	i = 0;
	j = 0;
	is_equal = FALSE;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '=')
			is_equal = TRUE;
		i++;
	}
	if (type == DEAL_ENV && is_equal == FALSE)
		return (NULL);
	if (is_equal == TRUE && type == DEAL_EXPORT)
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1 + 2);
	// if (ft_get_quotes(str) > 0)
	// {
	//     str = move_quotes(str);
	//     tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	// }
	if (!tmp)
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	// else
		// tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (is_equal == TRUE && type == DEAL_EXPORT && str[i] == '=')
		{
			tmp[j] = str[i];
			tmp[++j] = '\"';
			i++;
			j++;
			continue ;
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	if (is_equal == TRUE && type == DEAL_EXPORT)
	{
		tmp[j] = '\"';
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	add_end_list(char *str, t_element *first, int type, t_control *control)
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
		first->control = control;
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
	first->control = control;
	tmp->next = tmp2;
	return (SUCCESS);
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
	first->control = NULL;
	return (first);
}

void    ft_print_export(t_element *first, t_bool bool)
{
	t_element *tmp;

	tmp = first;
	if (!first)
		return ;
	while (tmp)
	{
		if (bool == TRUE)
			ft_printf_fd(1, "export ");
		ft_printf_fd(1 ,"%s\n", tmp->str);
		// ft_printf_fd(1 ,"%s\n", tmp->var_name);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return ;
}

int ft_get_new_var(t_control *list, char **newargv)
{
	int			i;
	t_element	*new;
	t_element	*tmp;
	char		*retreat;

	i = 0;
	while (newargv[++i])
	{
		//TODO: PBM WITH SPACES : AB is dealing
		//TODO: check with quotes, empty quotes, and only =
			//if only =, do not modify values
		printf(PINK"newargv is %s\n"END, newargv[i]);
		//think about removing it
		retreat = ft_remove_quotes(newargv[i]);
		printf(YELLOW"new str is %s\n"END, retreat);
		tmp = ft_is_in_list(list, retreat);
		if ((retreat[0] <= '9' && retreat[0] >= '0') || (ft_is_space_before_qual(retreat)))
		{
			ft_printf_fd(1, "\"%s\" : not a valid identifier\n", retreat);
			free(retreat);
			free(tmp);
			continue ;
		}
		if (tmp)
		{
			if (!ft_strchr(retreat, '='))
			{
				free(retreat);
				continue ;
			}
			free(tmp->str);
			tmp->str = ft_strdup(retreat);
			free(retreat);
			continue ;
		}
		if (list->first_env_var->str == NULL)
		{
			list->first_env_var->str = ft_strdup(retreat);
			list->first_env_var->var_name = add_var_name(list->first_env_var->str);
			free(retreat);
			continue ;
		}
		tmp = list->first_env_var;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new = malloc(sizeof(*new));
		if (!new)
			return (FAILURE);
		new->str = ft_strdup(retreat);
		free(retreat);
		new->var_name = add_var_name(new->str);
		new->next = NULL;
		new->index = i;
		tmp->next = new;
	}
	return (1);
}

int	ft_add_new_var(t_control *list, int type)
{
	t_element	*tmp;

	tmp = list->first_env_var;
	// printf("first is %s", tmp->str);
	if (!tmp)
		return (FAILURE);
	while (tmp && tmp->str)
	{
		//TODO: add " " if =
		if (type == DEAL_EXPORT)
		{
			add_end_list(tmp->str, list->first_export, DEAL_EXPORT, list);
		}
		else
		{
			add_end_list(tmp->str, list->first_env, 0, list);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (SUCCESS);
}

// EXPORT BUGS

//TODO: problem with spacing
//TODO: IF NAME ALREADY EXIST, do nothing

/* Liste toutes les variables d’environnement dans l’ordre ascii.
sous la forme : declare -x nom=”valeur” ou declare -x nom */
int	ft_export(t_control *list, char **newargv)
{
	(void)newargv;
	// ft_print_stuff(list->first_export, "export list");
	ft_add_new_var(list, DEAL_EXPORT);
	ft_print_export(list->first_export, TRUE);
	// ft_print_stuff(list->first_env_var, "first env var list");
	free_all(list);
	return (1);
}

void	ft_remove_first_env(t_control *control)
{
	t_element *tmp;

	if(control->first_env_var == NULL)
		return ;
	tmp = control->first_env_var;
	control->first_env_var = control->first_env_var->next;
	free(tmp->var_name);
	free(tmp->str);
	free(tmp);
}
/* liste toutes les variables d’environnement dans un ordre random. sous la forme : nom=valeur */
int	ft_env(t_control *list)
{
	// ft_add_new_var(list, DEAL_ENV);
	// ft_print_export(list->first_env, FALSE);
	printf("list->first is of address [%p]\n", list->first_env_var);
	// printf("list->first is of addrress [%p]\n", list->first_env_var);
	// ft_print_stuff(list->first_env_var, "first env var list");
	free_all(list);
	return (1);
}
