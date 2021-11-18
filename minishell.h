/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:17 by abrun             #+#    #+#             */
/*   Updated: 2021/11/18 14:23:13 by abrun            ###   ########.fr       */
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
# include <sys/wait.h>

		//	MACROS
#define FAILURE -1
#define SUCCESS 0
#define PINK "\033[95m"
#define END "\033[0m"
#define YELLOW "\033[93m"
#define RED "\033[91m"

		// STRUCTURES
typedef struct s_element
{
    char *str;
    struct s_element *next;
} t_element;

typedef struct s_control
{
    t_element *first;
} t_control;

		//	OPEN_TERM.C

int		open_term(void);

char	**init_xterm(void);


		//	INIT_PATHS.C

char	**init_paths(char **envp);

char	**fill_paths(char *line, int count);

int		get_path_len(char *line, int count);

char	*ft_add_one_path(char *line, int *count);


		//	EXEC_CMD.C

int		exec_cmd(char *cmd_line, char **paths, t_control *list);

char	*init_cmd_path(char *cmd, char **paths);


		//	PROMPT_MSG.C

char	*prompt_msg(void);


		//	FT_BUILTINS.C

int		ft_builtins(char **newargv, t_control *list);

int		is_builtins(char *newargv);


		//	FT_ECHO.C

int		ft_echo(char **newargv);

void	write_newargv(char **newargv, int c);


		//	FT_PWD.C

int		ft_pwd(char **newargv);


		//	FT_CD.C

int		ft_cd(char **newargv);


		//	FT_CMD.C

int		ft_cmd(char ***newargv, char **paths, t_control *list);

int		get_n_cmd(char *cmd_line);


		//	INIT_NEWARGV.C

char	***init_newargv(char *cmd_line, char **paths);

int		ft_split_len(char **split);


		//	TOOLS.C

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

		// EXPORT.C

int 	ft_export(t_control *list);

void    ft_print_export(t_element *first);

t_control *ft_init();

void 	add_end_list(char *str, t_control *list);

char 	*add_str(char *str);

		//	FT_READ_INPUT.C

int		ft_read_input(char **newargv, char **paths, int *fds);

char	*get_heredoc(char *lim);

char	**init_new(char **newargv, char **paths);

int		init_param_heredoc(char *lim, char **buf, char **heredoc, int *ret);

		//	FREE GARBAGE COLLECTOR

void free_all(t_control *control);

void free_elms(t_element *first);
#endif
