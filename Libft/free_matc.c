/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:43:44 by abrun             #+#    #+#             */
/*   Updated: 2021/12/14 16:23:36 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_matc(char **matc)
{
	int		n;

	n = 0;
	while (matc[n])
	{
		if (matc[n])
			free(matc[n]);
		n++;
	}
	free(matc);
}
