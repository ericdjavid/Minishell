/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:08:32 by edjavid           #+#    #+#             */
/*   Updated: 2021/12/17 20:15:31 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_bad_entries(char *str)
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
	if (sq % 2 != 0 || dq % 2 != 0)
		return (TRUE);
	return (FALSE);
}
