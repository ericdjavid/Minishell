/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:16:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 17:14:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_n_digit(int n)
{
	int	res;
	int	minus;

	minus = 0;
	if (n < 0)
	{
		n *= -1;
		minus = 1;
	}
	res = 1;
	while (n > 10)
	{
		n /= 10;
		res++;
	}
	if (minus)
		res++;
	return (res);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		counter;
	int		n_digit;

	n_digit = ft_n_digit(n);
	itoa = malloc(sizeof(n_digit + 1));
	if (!itoa)
		return (0);
	counter = n_digit - 1;
	if (n < 0)
	{
		itoa[0] = '-';
		n *= -1;
	}
	ft_getnbr(itoa, n, counter);
	itoa[n_digit] = 0;
	return (itoa);
}

void	ft_getnbr(char *itoa, int n, int counter)
{
	if (n / 10 > 0)
		ft_getnbr(itoa, n / 10, counter - 1);
	itoa[counter] = n % 10 + '0';
}
