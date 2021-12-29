/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:56:08 by abrun             #+#    #+#             */
/*   Updated: 2021/12/29 16:54:39by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***init_newargv(char *cmd_line, char **paths)
{
	char	***newargv;
	int		c_1;
	int		c_2;
	int		c;
	char	**split;

	newargv = init_param_in(&split, cmd_line, &c_1, &c);
	if (!newargv)
		return (0);
	while (split[c])
	{
		newargv[c_1] = malloc(sizeof(char *) * (ft_split_len(split, c) + 1));
		if (!newargv[c_1])
			return (free_init_new(newargv, split));
		c_2 = 0;
		while (split[c] && ft_strncmp(split[c], "|", ft_strlen(split[c])))
			newargv[c_1][c_2++] = split[c++];
		newargv[c_1][0] = init_cmd_path(newargv[c_1][0], paths);
		if (split[c])
			free(split[c++]);
		newargv[c_1++][c_2] = 0;
	}
	newargv[c_1] = 0;
	free(split);
	return (newargv);
}

char	*ft_append(char *cmd_line, int pos)
{
	int		i;
	int		j;
	char	*snew;

	i = 0;
	j = 0;
	snew = malloc(sizeof(char) * (ft_strlen(cmd_line) + 1 + 100));
	if (!snew)
		return NULL;
	while (cmd_line[i] && i < pos)
	{
		snew[i] = cmd_line[i];
		i++;
	}
	printf("is is %d and j is %d", i, j );
	j = i;
	snew[j] = ' ';
	j++;
	while (cmd_line[i] != '\0')
	{
		snew[j] = cmd_line[i];
		i++;
		j++;
	}
	snew[j] = 0;
	printf(PINK "NEW str is |%s|\n" END, snew);
	free(cmd_line);
	return (snew);
}

char	*add_spaces_to_cmd_line(char *cmd_line)
{
	int	i;

	if (!(ft_strchr(cmd_line, '"')) && !(ft_strchr(cmd_line, '\'')))
		return (cmd_line);
	i = 0;
	while(cmd_line[i])
	{
		if (cmd_line[i] == '\'')
		{
			if (i >= 1 && cmd_line[i - 1] != ' ')
			{
				cmd_line = ft_append(cmd_line, i);
				i++;
			}
			i++;
			while (cmd_line[i] && cmd_line[i] != '\'')
				i++;
			i++;
			cmd_line = ft_append(cmd_line, i);
		}
		if (cmd_line[i] == '"')
		{
			if (i >= 1 && cmd_line[i - 1] != ' ')
			{
				cmd_line = ft_append(cmd_line, i);
				i++;
			}
			i++;
			while (cmd_line[i] && cmd_line[i] != '"')
				i++;
			i++;
			cmd_line = ft_append(cmd_line, i);
		}
		i++;
	}
	return (cmd_line);

}

char	***init_param_in(char ***split, char *cmd_line, int *c_1, int *c)
{
	char	***newargv;
	char	charset[3];
	// char	*new_cmd_line;

	// new_cmd_line = ft_strdup(cmd_line);
	// cmd_line = add_spaces_to_cmd_line(new_cmd_line);
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

	// free(cmd_line);
	return (newargv);
}

int	ft_split_len(char **split, int c)
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
