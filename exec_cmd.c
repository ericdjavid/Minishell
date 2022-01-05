/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:10:39 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/05 19:08:31 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_line, char **paths, t_control *list)
{
	char	***newargv;
	char	*new_line;
	int		ret;
	int		i;

	ret = 1;
	i = 0;
	while (*cmd_line && *cmd_line == 32)
		cmd_line++;
	if (!*cmd_line)
		return (1);
	new_line = get_new_line(cmd_line, list, &i);
	if (i == 1)
		return (-1);
	if (!new_line)
		return (-2);
	newargv = init_newargv(new_line, paths);
	if (!newargv)
	{
		free(new_line);
		return (1);
	}
	if (ft_3dimlen(newargv + 1) == 1 && is_builtins(newargv[1][0]))
		ret = exec_builtins(&newargv[1], list, paths);
	else
		ft_cmd(newargv, paths, list, n_pid(newargv));
	return (exit_exec(ret, newargv, new_line));
}

int	ft_deal_bad(char *str, int count, char c, char d)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && no_unpair_char_before(str, i, d))
		{
			while (str[i] != '\0')
			{
				if (str[i] == c)
					count++;
				i++;
			}
			if (count % 2 != 0)
			{
				free(str);
				return (1);
			}
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

int	ft_deal_bad_sq_dq(char *str)
{
	int	count;

	count = 0;
	if (ft_deal_bad(str, count, '\'', '"') == 1)
		return (-1);
	if (ft_deal_bad(str, count, '"', '\'') == 1)
		return (-1);
	return (SUCCESS);
}

char	*get_new_line(char *cmd_line, t_control *list, int *i)
{
	char	*new_line;
	int		is_mal;
	int		count;

	count = 0;
	is_mal = 0;
	new_line = ft_strdup(cmd_line);
	if (!new_line)
		return (0);
	new_line = ft_is_dollar2(new_line, list, is_mal, count);
	if (!new_line)
		return (0);
	if (ft_deal_bad_sq_dq(new_line) == -1)
	{
		*i = 1;
		return (0);
	}
	new_line = put_sp_around_pipes(new_line);
	if (!new_line)
		return (0);
	return (new_line);
}

void	free_newargv(char ***matc)
{
	int	n;

	n = 1;
	while (matc[n])
	{
		free_matc(matc[n]);
		n++;
	}
	free(matc);
}

char	*put_sp_around_pipes(char *str)
{
	char	*new;
	int		c_1;
	int		c_2;

	new = NULL;
	new = init_param_put_sp(str);
	if (!new)
		return (0);
	c_2 = 0;
	c_1 = 0;
	while (str[c_1])
	{
		if (str[c_1] == '|')
		{
			new[c_1 + c_2++] = 32;
			new[c_1 + c_2++] = '|';
			// while (str[c_1] && str[c_1] == '|')
			// {
			// 	new[c_1 + c_2] = '|';
			// 	c_1++;
			// }
			// c_2++;
			new[c_1 + c_2] = 32;
		}
		// else if (str[c_1] == '<')
		// {
		// 	new[c_1 + c_2++] = 32;
		// 	while (str[c_1] && str[c_1] == '<')
		// 	{
		// 		new[c_1 + c_2] = '<';
		// 		c_1++;
		// 	}
		// 	new[c_1 + c_2] = 32;
		// 	c_2++;
		// }
		else
			new[c_1 + c_2] = str[c_1];
		c_1++;
	}
	new[c_1 + c_2] = 0;
	// printf("new : %s\n", new);
	free(str);
	return (new);
}

char	*init_param_put_sp(char *str)
{
	char	*new;
	int		c_1;
	int		c_2;

	if (!str)
		return (0);
	c_2 = 0;
	c_1 = 0;
	while (str[c_1])
	{
		if (str[c_1] == '|')
		{
			while (str[c_1] && str[c_1] == '|')
				c_1++;
			c_2 += 2;
		}
		else if (str[c_1] == '<')
		{
			while (str[c_1] && str[c_1] == '<')
				c_1++;
			c_2 += 2;
		}
		else
			c_1++;
	}
	new = malloc(c_1 + c_2 + 1);
	if (!new)
	{
		free(str);
		return (0);
	}
	return (new);
}
