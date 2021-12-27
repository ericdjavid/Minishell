/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:55:51 by abrun             #+#    #+#             */
/*   Updated: 2021/12/27 15:56:34 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "../minishell.h"
# include "../Libft/libft.h"
# include <stdarg.h>

int		ft_printf_fd(int fd, const char *s, ...);

int		print_arg(char c, va_list lst, int fd);

int		print_d(int arg, int fd);

int		print_s(char *arg, int fd);

int		print_x(unsigned int arg, int fd);

int		ft_n_digit(int n);

char	*ft_itoa(int n);

void	ft_getnbr(char *itoa, int n_bis, int counter);

char	*convert_hexa(unsigned int n);

int		get_n_hexa(unsigned int n);

char	*get_hexa_base(void);
#endif
