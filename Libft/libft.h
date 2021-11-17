/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:18:03 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 13:50:06 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

char	*ft_strdup(const char *s);

void	free_matc(char **matc);

size_t	ft_strlen(const char *s);

void	print_matc(char **matc);

int		ft_strncmp(const char *s1, const char *s2, size_t len);

void	ft_strcpy(char *dst, const char *str);

void	ft_strcat(char *dst, const char *str);

char	**ft_split(char *s, char c);
#endif
