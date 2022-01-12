/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:56:08 by abrun             #+#    #+#             */
/*   Updated: 2022/01/12 15:06:00 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***init_newargv(char *cmd_line, char **paths)
{
	char	***newargv;
	int		c[3];
	char	**spl;

	(void)paths;
	c[1] = 0;
	newargv = init_param_in(&spl, cmd_line, &c[1], &c[0]);
	if (!newargv)
		return (0);
	while (spl[c[0]])
	{
		newargv[c[1]] = malloc(sizeof(char *) * (ft_splen(spl, c[0]) + 1));
		if (!newargv[c[1]])
			return (free_init_new(newargv, spl));
		c[2] = 0;
		newargv[c[1]][0] = NULL;
		while (spl[c[0]] && ft_strncmp(spl[c[0]], "|", ft_strlen(spl[c[0]])))
			newargv[c[1]][c[2]++] = spl[c[0]++];
		if (spl[c[0]])
			free(spl[c[0]++]);
		newargv[c[1]++][c[2]] = 0;
	}
	newargv[c[1]] = 0;
	free(spl);
	return (newargv);
}

char	***init_param_in(char ***split, char *cmd_line, int *c_1, int *c)
{
	char	***newargv;
	char	charset[3];

	newargv = malloc(sizeof(char **) * (get_n_cmd(cmd_line) + 2));
	if (!newargv)
		return (0);
	charset[0] = 32;
	charset[1] = 9;
	charset[2] = 0;
	*split = ft_split(cmd_line, &charset[0]);
	if (!*split || is_syntax_er_spl(*split))
	{
		free(newargv);
		return (0);
	}
	newargv[0] = 0;
	*c_1 = 1;
	*c = 0;
	return (newargv);
}

int	ft_splen(char **split, int c)
{
	int	len;

	len = 0;
	while (split[c + len] && ft_strncmp(split[c + len], "|",
			ft_strlen(split[c + len])))
		len++;
	return (len);
}

char	***free_init_new(char ***newargv, char **split)
{
	free_3dim_matc(newargv);
	free_matc(split);
	return (0);
}

int	is_syntax_er_spl(char **split)
{
	int	c_1;
	int	c_2;

	c_1 = 0;
	while (split[c_1])
	{
		c_2 = 0;
		while (split[c_1 + c_2] && split[c_1 + c_2][0] == '|')
			c_2++;
		if (c_2 > 1)
		{
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `|'\n");
			free_matc(split);
			g_status = 2;
			return (1);
		}
		c_1++;
	}
	return (0);
}
