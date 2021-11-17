/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:17 by abrun             #+#    #+#             */
/*   Updated: 2021/11/17 17:44:12 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "Libft/libft.h"
# include "Printf/printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


		//	OPEN_TERM.C

int		open_term(void);

char	**init_xterm(void);


		//	INIT_PATHS.C

char	**init_paths(char **envp);

char	**fill_paths(char *line, int count);

int		get_path_len(char *line, int count);

char	*ft_add_one_path(char *line, int *count);


		//	EXEC_CMD.C

int		exec_cmd(char *cmd_line, char **paths);

char	*init_cmd_path(char *cmd, char **paths);

int		ft_non_builtins(char **newargv);


		//	PROMPT_MSG.C

char	*prompt_msg(void);


		//	FT_BUILTINS.C

int		ft_builtins(char **newargv);


		//	FT_ECHO.C

int		ft_echo(char **newargv);

void	write_newargv(char **newargv, int c);


		//	FT_PWD.C

int		ft_pwd(char **newargv);


		//	FT_CD.C

int		ft_cd(char **newargv);
#endif
