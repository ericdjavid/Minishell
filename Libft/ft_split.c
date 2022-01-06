/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:07:16 by abrun             #+#    #+#             */
/*   Updated: 2022/01/06 12:12:19 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char *str, char *charset)
{
	int		n_cases;
	char	**split;
	int		count;

	if (!str)
		return (NULL);
	n_cases = get_n_cases(str, charset);
	split = malloc(sizeof(char *) * (n_cases + 1));
	if (!split)
		return (0);
	count = 0;
	while (*str && count < n_cases)
	{
		str = get_next_str(str, charset, count);
		split[count] = fill_split(str, charset);
		if (!split[count])
		{
			free_matc(split);
			return (0);
		}
		count++;
	}
	split[count] = NULL;
	return (split);
}
