/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:17 by abrun             #+#    #+#             */
/*   Updated: 2021/12/10 22:07:38 by edjavid          ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

		//	MACROS
# define FAILURE 1
# define SUCCESS 0
# define PINK "\033[95m"
# define END "\033[0m"
# define YELLOW "\033[93m"
# define RED "\033[91m"

extern int	status;

# define DEAL_EXPORT 1
# define DEAL_ENV 0
# define NEO_ENV 2

		// STRUCTURES
typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_element
{
	char				*str;
	char				*var_name;
	int					index;
	struct s_element	*next;
	struct s_control			*control;
}	t_element;

typedef struct s_control
{
	t_element	*first_env;
	t_element	*first_export;
	t_element	*first_env_var;
	int			size;
	int			size_env;
}	t_control;

		//	MINISHELL.C

void	ft_minishell(char **paths, t_control *list);

void	sigint_handler(int sig);

		//	INIT_PATHS.C

char	**init_paths(char **envp);

char	**fill_paths(char *line, int count);

int		get_path_len(char *line, int count);

char	*ft_add_one_path(char *line, int *count);

		//	EXEC_CMD.C

int		exec_cmd(char *cmd_line, char **paths, t_control *list);

char	*init_cmd_path(char *cmd, char **paths);

void	free_newargv(char ***matc);

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

char	*get_absolutePath(void);

		//	FT_CMD.C

int		ft_cmd(char ***newargv, char **paths, t_control *list);

int		*init_ret(void);

int		**init_fds(void);

int		status_free(int **fds);

int		get_n_cmd(char *cmd_line);

		//	INIT_NEWARGV.C

char	***init_newargv(char *cmd_line, char **paths);

char	***init_param_in(char ***split, char *cmd_line, int *c_1, int *c_spl);

int		ft_split_len(char **split, int c_spl);

char	***free_init_new(char ***newargv, char **split);

int		is_syntax_er_spl(char **split);

		//	TOOLS.C

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

void	ft_is_dollar(char **str, t_control *control);

t_element	*ft_is_in_list(t_control *list, char *str);

t_element	*check_in_list(t_element *first, char *str);

		// EXPORT.C

int			ft_export(t_control *list, char **newargv);

void    	ft_print_export(t_element *first, t_bool bool);

t_element 	*ft_init();

int			add_end_list(char *str, t_element *first, int type, t_control *control);

char 		*add_var_name(char *str);

char 		*add_str2(char *str, int type);

int			ft_init_list(t_control *list, char **envp);

t_bool		check_order(t_control *list);

int			order_ascii(t_control *list);

int			ft_get_new_var(t_control *list, char **newargv);

char    	*ft_remove_quotes(char *str);

int			ft_add_new_var(t_control  *list, int type);

		// FT_ENV.C

int 		ft_env(t_control *list);

		//	FT_READ_INPUT.C

int		ft_read_input(char ***newargv, char **paths);

char		*get_heredoc(char *lim);

int			init_param_heredoc(char *lim, char **buf, char **heredoc, int *ret);

char		**get_newargv_rdin(char **newargv, int c, char **paths);

char		*ft_strdup_rdin(char *s, char **mat1, char **mat2);

		//	FT_REDIRECTION.C

int			ft_redirection(char ***newargv);

int			which_redirection(char *s);

int			get_outfd(char *file, int config);

char		**get_new_redir(char **newargv, int redir);

char		**free_redirection(char **newargv, char **new);

int			*assign_config(int *ret, int config);

int			exit_redirection(int *ret);

		// FT_LINKED_LISTS

char		*is_in_list(t_element *first, char *str);

void 		add_index(t_element *elem);

char	*ft_get_parsed_env(char *str);


int			ft_init_list(t_control *list, char **envp);

		//	FREE GARBAGE COLLECTOR

void		free_all(t_control *control);

void		free_elms(t_element *first);

		//	FT_MANAGE_FDS.C

int		*ft_manage_fds(char ***newargv, char **paths, int **fds);

int		check_ret_stdin(int *ret);

int		check_ret_stdout(int *ret);

		//	FT_CHILD.C

int		ft_child(char ***newargv, char **paths, t_control *list, int **fds);

		//	FT_UNSET.C

int		ft_unset(t_control *control, char **newargv);

int		ft_print_stuff(t_element *first, char *str);

		//	TOOLS2.C

int		ft_is_space_before_qual(char *str);

void	ft_remove_env(t_control *list);

#endif
