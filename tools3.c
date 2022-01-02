/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:08:32 by edjavid           #+#    #+#             */
/*   Updated: 2022/01/02 16:24:20 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pair(char *str, t_bool *sq_pair, t_bool *dq_pair)
{
	int	sq;
	int	dq;
	int	i;

	if (!str)
		return (TRUE);
	sq = 0;
	dq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			sq++;
		if (str[i] == '\"')
			dq++;
	}
	if (sq % 2 != 0)
		*sq_pair = FALSE;
	if (dq % 2 != 0)
		*dq_pair = FALSE;
	if ((*sq_pair == TRUE) && (*dq_pair == TRUE))
		return (TRUE);
	return (FALSE);
}

t_bool	is_surrounded(char *str, size_t size, char c)
{
	if (str[0] == c && str[size] == c)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_str_bad_entry(char *str)
{
	t_bool	sq_pair;
	t_bool	dq_pair;
	size_t	size;

	sq_pair = TRUE;
	dq_pair = TRUE;
	size = ft_strlen(str) - 1;
	if (!(is_pair(str, &sq_pair, &dq_pair)))
	{
		printf("dq pair is %d amd sq ppair is %d\n", dq_pair,  sq_pair);
		printf("str h i 0 = %c and last is %c\n", str[0], str[size]);
		if (str[0] == '\'' && str[size] == '\'' && sq_pair == FALSE)
			return (TRUE);
		if (str[0] == '\"' && str[size] == '\"' && dq_pair == FALSE)
			return (TRUE);
		if (is_surrounded(str, size, '\'') == FALSE && is_surrounded(str, size, '\"') == FALSE &&
			(sq_pair == FALSE || dq_pair == FALSE))
		{
			printf("it s inside\n");
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	ft_bad_entries(char **str)
{
	int i;
	t_bool	sq_pair;
	t_bool	dq_pair;
	size_t	size;

	sq_pair = TRUE;
	dq_pair = TRUE;
	i = -1;
	while (str[++i])
	{
		printf(RED"str to process : %s\n"END, str[i]);
		size = ft_strlen(str[i]) - 1;
		if (!(is_pair(str[i], &sq_pair, &dq_pair)))
		{
			printf("dq pair is %d amd sq ppair is %d\n", dq_pair,  sq_pair);
			printf("str h i 0 = %c and last is %c\n", str[i][0], str[i][size]);
			if (str[i][0] == '\'' && str[i][size] == '\'' && sq_pair == FALSE)
				return (TRUE);
			if (str[i][0] == '\"' && str[i][size] == '\"' && dq_pair == FALSE)
				return (TRUE);
			if (is_surrounded(str[i], size, '\'') == FALSE && is_surrounded(str[i], size, '\"') == FALSE &&
				(sq_pair == FALSE || dq_pair == FALSE))
			{
				printf("it s inside\n");
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

char	*ft_is_dollar3(t_control *control, char *new_str)
{
	char	*str_good;

	str_good = is_in_list(control->first_env, new_str);
	if (str_good == NULL)
		str_good = is_in_list(control->first_env_var, new_str);
	if (str_good == NULL && new_str[1] == '?')
		str_good = ft_itoa(g_status);
	return (str_good);
}

int		no_unpair_char_before(char *str, int i, char c)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (i == 0)
		return (1);
	while (str[j] && j < i)
	{
		if (str[j] == c)
			count++;
		j++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

char	*ft_strcut(char *str, int size, int pos)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	i = 0;
	j = 0;
	while (str[i] && i < pos)
	{
		new[j] = str[i];
		j++;
		i++;
	}
	i += size;
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*ft_is_dollar2(char *str, t_control *control, int *modif)
{
	int		i;
	char	*str_good;
	char	*new_str;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] && str[i] == '\'' && no_unpair_char_before(str, i, '"'))
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] != '\'')
				break ;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
		{
			new_str = get_new_str(str, i, &size);
			str_good = ft_is_dollar3(control, new_str);
			if (str_good == NULL)
			{
				str = ft_strcut(str, size, i);
				//TODO : can t do it, need to modify value of $nothing to nothin in the string
				*modif = 0;
				free(new_str);
				i++;
				continue ;
			}
			free(new_str);
			if (str_good != NULL)
			{
				str = get_new_line_cmd(str, i, size, str_good);
				if (str[i + 1] == '?')
					free(str_good);
				i = -1;
				continue ;
			}
		}
	}
	return (str);
}

char	*get_new_line_cmd(char *str, int i, int size, char *str_good)
{
	char	*neo_line_cmd;
	int		j;
	int		k;

	neo_line_cmd = malloc(sizeof(char) * ((int)ft_strlen(str_good)
				+ (int)ft_strlen(str) - size + 1));
	j = -1;
	while (str[++j] && j < i)
		neo_line_cmd[j] = str[j];
	k = -1;
	while (str_good[++k] && k < (int)ft_strlen(str_good))
	{
		neo_line_cmd[j] = str_good[k];
		j++;
	}
	k = (i + size);
	while (str[k])
	{
		neo_line_cmd[j] = str[k];
		j++;
		k++;
	}
	free(str);
	neo_line_cmd[j] = '\0';
	return (neo_line_cmd);
}
