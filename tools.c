/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:24:21 by abrun             #+#    #+#             */
/*   Updated: 2021/12/17 19:07:31 by edjavid          ###   ########.fr       */
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
		return (FALSE);
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
	{
		if (str2)
			free(str2);
		return (tmp2);
	}
	if (str2)
		free(str2);
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
	if (fd == 0 || fd == 1)
		return ;
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}

//to delete
// TODO:segault if $var is not found
// TODO: display the var if "", but don't if ''
void	ft_is_dollar(char **str, t_control *control)
{
	int		i;
	char	*str_good;

	(void) control;
	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '$' && str[i][1] != ' '
			&& str[i][1] && str[i][1] != '?')
		{
			str_good = is_in_list(control->first_env, str[i]);
			if (str_good == NULL)
				str_good = is_in_list(control->first_env_var, str[i]);
			if (str_good != NULL)
			{
				// printf("found\n");
				free(str[i]);
				str[i] = ft_strdup(str_good);
			}
			else
			{
				// printf("modifiying value \n");
				free(str[i]);
				// str[i] = ft_strdup("");
				str[i] = NULL;
			}
		}
	}
	return ;
}

char	*get_new_str(char *str, int i, int *size)
{
	int j;
	int k;
	char *new_str;

	j = i + 1;
	while (str[j] && str[j]  != '\0' && str[j] != '$' && str[j] != ' ' && str[j] != '\"')
		j++;
	*size = j - i;
	// printf("malloc of new str is %d\n", j - i);
	new_str = malloc(sizeof(char) * (j - i + 1));
	k = 0;
	new_str[k] = '$';
	i++;
	k++;
	while (str[i] && str[i]  != '\0' && str[i] != '$' && str[i] != ' ' && str[i] != '\"')
	{
		new_str[k] = str[i];
		k++;
		i++;
	}
	new_str[k] = '\0';
	return (new_str);
}

char	*get_new_line_cmd(char *str,int i, int size, char *str_good)
{
	char	*neo_line_cmd;
	int		j;
	int		k;


	printf("i is %d and size of $var called is %d\n", i, size);
	printf("Malloc of new line cmd size is %d\n" , (int)ft_strlen(str_good) + (int)ft_strlen(str) - size + 1);
	neo_line_cmd = malloc(sizeof(char) * ((int)ft_strlen(str_good) + (int)ft_strlen(str) - size + 1));
	j = 0;;
	while (str[j] && j < i )
	{
		neo_line_cmd[j] = str[j];
		j++;
	}
	k = 0;
	while (str_good[k] && k < (int)ft_strlen(str_good))
	{
		neo_line_cmd[j] = str_good[k];
		j++;
		k++;
	}
	k = (i + size);
	while (str[k])
	{
		neo_line_cmd[j] = str[k];
		j++;
		k++;
	}
	if (str)
		free(str);
	neo_line_cmd[j] = '\0';
	return (neo_line_cmd);
}

char *ft_is_dollar2(char *str, t_control *control)
{
	int		i;
	char	*str_good;
	char	*new_str;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' '
			&& str[i + 1] && str[i + 1] != '?')
		{
			new_str = get_new_str(str, i, &size);
			printf("new str is %s and size is %d\n", new_str, size);
			str_good = is_in_list(control->first_env, new_str);
			if (str_good == NULL)
				str_good = is_in_list(control->first_env_var, new_str);
			printf(RED"new str good is %s \n"END, str_good);
			if (str_good != NULL)
			{
				printf(RED"old line cmd is |%s| \n"END, str);
				str = get_new_line_cmd(str, i, size, str_good);
				printf(RED"new line cmd is |%s| \n"END, str);
				i = 0;
				free(new_str);
				continue ;
			}
			if (new_str)
				free(new_str);
		}
		i++;
	}
	return (str);
}

