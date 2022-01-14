/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:25:02 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 11:43:55 by abrun            ###   ########.fr       */
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

int	ft_add_from_list(char **neo_env, t_element *first, int i)
{
	t_element	*tmp;

	tmp = first;
	if (!tmp)
		return (FAILURE);
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		neo_env[i] = ft_fill_env(tmp);
		i++;
		tmp = tmp->next;
	}
	return (i);
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
	i = ft_add_from_list(neo_env, list->first_env, i);
	tmp = list->first_env_var;
	while (tmp && tmp->str)
	{
		neo_env[i] = ft_strdup(tmp->str);
		i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	neo_env[i] = 0;
	return (neo_env);
}

void	close_fds_in_child2(int **fds, char ***prev, int *ret)
{
	int	n;

	n = fds[0][0];
	ft_close_fd(1);
	if (prev)
		ft_close_fd(0);
	ft_close_fd(fds[n][1]);
	while (fds[++n])
		ft_close_fd(fds[n][1]);
	if (fds[0][0] > 2)
		ft_close_fd(fds[fds[0][0] - 2][0]);
	if (fds[0][0] > 1 && ret[0])
		ft_close_fd(fds[fds[0][0] - 1][0]);
}

int	close_fds_in_child(int **fds, int builtins, char ***prev, int *ret)
{
	int	n;

	if (builtins)
	{
		close_fds_in_child2(fds, prev, ret);
	}
	else
	{
		n = fds[0][0];
		ft_close_fd(fds[n][1]);
		ft_close_fd(1);
		while (fds[++n])
			ft_close_fd(fds[n][1]);
	}
	free(ret);
	exit(g_status);
}
