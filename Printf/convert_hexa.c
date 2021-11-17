/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:58:24 by abrun             #+#    #+#             */
/*   Updated: 2021/11/09 09:34:03 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*convert_hexa(unsigned int n)
{
	char	*hexa;
	int		n_hexa;
	char	*base;
	int		counter;

	n_hexa = get_n_hexa(n);
	base = get_hexa_base();
	if (!base)
		return (0);
	hexa = malloc(n_hexa + 1);
	if (!hexa)
	{
		free(base);
		return (0);
	}
	counter = 1;
	while (n > 0)
	{
		hexa[n_hexa - counter] = base[n % 16];
		n /= 16;
		counter++;
	}
	hexa[n_hexa] = 0;
	return (hexa);
}

int	get_n_hexa(unsigned int n)
{
	int	n_hexa;

	n_hexa = 0;
	while (n > 0)
	{
		n /= 16;
		n_hexa++;
	}
	return (n_hexa);
}

char	*get_hexa_base(void)
{
	char	*base;
	int		c;

	base = malloc(17);
	if (!base)
		return (0);
	c = 0;
	while (c < 10)
	{
		base[c] = '0' + c;
		c++;
	}
	while (c < 16)
	{
		base[c] = 'a' + c - 10;
		c++;
	}
	base[c] = 0;
	return (base);
}
