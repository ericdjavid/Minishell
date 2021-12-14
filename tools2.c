/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:40:53 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/14 12:02:26 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = dst;
	n = size;
	s = src;
	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}



char	*ft_get_dollar_var(char *str, t_control *list)
{
	int			i;
	t_element	*tmp;
	char		*tmp_char;

	i = 0;
	tmp_char = NULL;
	(void) list;
	while (str[++i] && str[i] != '$')
		;
	tmp_char = malloc(sizeof(char) * (i + 1));
	if (!tmp_char)
		return (NULL);
	ft_strlcpy(tmp_char, ++str, i);
	printf("tmp char is %s\n", tmp_char);
	tmp = ft_is_in_list(list, tmp_char);
	if (!tmp)
		return (NULL);
	//should return tmp->var value
	return (tmp->str);
}

int	ft_is_space_before_qual(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
