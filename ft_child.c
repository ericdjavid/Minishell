/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 18:23:41y edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_env(t_element *tmp)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(tmp->str) + 1));
	if (!str)
		return (NULL);
	while (tmp->str[i])
	{
		str[i] = tmp->str[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_get_envs_var(t_control *list)
{
	char		**neo_env;
	t_element	*tmp;
	int			i;

	i = 0;
	neo_env = malloc(sizeof(char *) * (list->size + 1));
	if (!neo_env)
		return (0);
	tmp = list->first_env;
	if (!tmp)
		return 0;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		neo_env[i] = ft_fill_env(tmp);
		i++;
		tmp = tmp->next;
	}
	//TODO: think I have to add also new envs
	neo_env[i] = 0;
	return (neo_env);
}

//  when deleting the folder where we are and pwd
// pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// TODO: test if free is good each time
int	ft_child(char ***newargv, char **paths, t_control *list, int **fds)
{
	int		*ret;
	char	**new_env;

	new_env = NULL;
	// ft_deal_SHLVL(list);
	new_env = ft_get_envs_var(list);
	// i = 0;
	// while (new_env[i])
	// {
	// 	printf("%s\n", new_env[i]);
	// 	i++;
	// }
	signal(SIGQUIT, SIG_DFL);
	ret = ft_manage_fds(newargv, paths, fds);
	if (!ret)
		exit(status);
	else if (ft_builtins(*newargv, list))
		;
	else if (access((*newargv)[0], F_OK))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n",
			(*newargv)[0]);
		status = 127;
	}
	else if (access((*newargv)[0], X_OK))
	{
		ft_printf_fd(2, "minishell: permission non accordée: %s\n",
			(*newargv)[0]);
		status = 126;
	}
	// rmplcacer NULL par les vars d env avec une valeur
	//  incrementer SHLVL au debut de minishell (si aucun set 1)
	else if (execve((*newargv)[0],
		(*newargv), new_env) < 0)
		status = 1;
	if (new_env)
		free_matc(new_env);
	free(ret);
	exit(status);
}
