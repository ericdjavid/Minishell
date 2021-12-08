/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:24:21 by abrun             #+#    #+#             */
/*   Updated: 2021/11/21 20:45:16 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_new_var_str(char *str)
{
	char	*str2;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	str2 = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != '\0' && str[i] != '=')
		str2[i] = str[i];
	str2[i] = '\0';
	printf("new str is |%s|\n", str2);
	return (str2);
}

t_bool	check_in_list(t_element *first, char *str)
{
	t_element *tmp;

	tmp = first;
	if (!tmp || !tmp->str || !tmp->var_name)
		return (FALSE);
	while (tmp)
	{
		printf(PINK"%s\n"END, tmp->var_name);
		if (ft_strncmp(str, tmp->var_name, ft_strlen(str)) == 0)
			return (TRUE);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (FALSE);
	
}

t_bool	ft_is_in_list(t_control *list, char *str)
{
	char *str2;

	str2 = NULL;
	str2 = get_new_var_str(str);
	if (check_in_list(list->first_export, str2) == TRUE
		|| check_in_list(list->first_env_var, str2) == TRUE)
	{
		free(str2);
		return (TRUE);
	}
	if (str2)
		free(str2);
	return (FALSE);
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->var_name);
	// 	if (ft_strncmp(str2, tmp->var_name, ft_strlen(str2)) == 0 
	// 		|| ft_strncmp(str2, tmp->var_name, ft_strlen(str2)) == 0)
	// 	{
	// 		free(str2);
	// 		return (TRUE);
	// 	}
	// 	if (tmp->next == NULL)
	// 		break ;
	// 	tmp = tmp->next;
	// }
	// free(str2);
	// return (FALSE);	
}

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}

void	ft_close_fd(int fd)
{
	if (fd == 0 || fd == 1)
		return ;
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}

void	ft_is_dollar(char **str, t_control *control)
{
	int		i;
	char	*str_good;

	(void) control;
	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '$' && str[i][1] != ' ')
		{
			str_good = is_in_list(control->first_env, str[i]);
			if (str_good == NULL)
				str_good = is_in_list(control->first_env_var, str[i]);
			// printf("Good str is |%s|\n", str_good);
			if (str_good != NULL)
			{
				free(str[i]);
				str[i] = ft_strdup(str_good);
			}
		}
	}	
	return ;
}