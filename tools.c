/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:24:21 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 16:50:08 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_var_str(char *str)
{
	char	*str2;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	str2 = malloc(sizeof(char) * (i + 1));
	if (!str2)
		return (NULL);
	i = -1;
	while (str[++i] != '\0' && str[i] != '=')
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}

t_element	*check_in_list(t_element *first, char *str)
{
	t_element	*tmp;

	tmp = first;
	if (!tmp || !tmp->str || !tmp->var_name)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(str, tmp->var_name, ft_strlen(str)) == 0)
			return (tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

t_element	*ft_is_in_list(t_control *list, char *str)
{
	char		*str2;
	t_element	*tmp1;
	t_element	*tmp2;

	str2 = NULL;
	str2 = get_new_var_str(str);
	tmp1 = check_in_list(list->first_export, str2);
	if (tmp1)
	{
		tmp2 = check_in_list(list->first_env, str2);
		free(tmp2->str);
		tmp2->str = ft_strdup(str);
		if (str2)
			free(str2);
		return (tmp1);
	}
	tmp2 = check_in_list(list->first_env_var, str2);
	if (tmp2)
		return (tmp2);
	return (NULL);
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
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}
