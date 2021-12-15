/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sign_digit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:09:56 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 16:45:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sign_digit(char *s, int c)
{
	if (ft_isdigit(s[c]))
		return (1);
	else if ((s[c] == '-' || s[c] == '+')
		&& (c == 0 || s[c - 1] == 32)
		&& (s[c + 1] && ft_isdigit(s[c + 1])))
		return (1);
	return (0);
}
