/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:18:03 by abrun             #+#    #+#             */
/*   Updated: 2021/11/22 15:08:14 by abrun            ###   ########.fr       */
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

int		ft_matlen(char **mat);

void	free_3dim_matc(char ***matc);

int		ft_strchr(const char *str, int chr);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strjoin_free_n(char *s1, const char *s2);

int		ft_matstr(char **mat, const char *str);

void	free_mati(int **mati, int m_len);

void	ft_putnbr_fd(long long int nb, int fd);
#endif
