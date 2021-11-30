/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:36:34 by abrun             #+#    #+#             */
/*   Updated: 2021/11/24 14:29:19 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_msg(void)
{
	char	*cmd_line;

	cmd_line = readline("\033[0;32m->  \033[0;34mMinishell \033[0;m");
	if (!cmd_line)
		write(1, "exit\n", 5); 
	add_history(cmd_line);
	return (cmd_line);
}
