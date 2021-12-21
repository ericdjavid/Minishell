/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:17 by abrun             #+#    #+#             */
/*   Updated: 2021/12/21 16:59:02 by edjavid          ###   ########.fr       */
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
}	t_element;

typedef struct s_control
{
	t_element	*first_env;
	t_element	*first_export;
	t_element	*first_env_var;
	int			size;
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

char	*put_spAroundPipes(char *str);

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

t_element	*check_in_list(t_element *first, char *str);

char	*get_new_str(char *str, int i, int *size);

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

char	*ft_get_good_str(char *str);

// void	ft_is_dollar(char **str, t_control *control);

char	*ft_is_dollar2(char *str, t_control *control);

t_element	*ft_is_in_list(t_control *list, char *str);

t_element	*check_in_list(t_element *first, char *str);

		// EXPORT.C

int			ft_export(t_control *list, char **newargv);

void		ft_print_export(t_element *first, t_bool bool);

int			add_end_list(char *str, t_element *first, int type);

char 		*add_var_name(char *str);

char 		*add_str2(char *str, int type);

t_bool		check_order(t_control *list);

int			order_ascii(t_control *list);

int			ft_get_new_var(t_control *list, char **newargv);

char		*ft_remove_quotes(char *str);

int			ft_add_new_var(t_control  *list, int type);

void		ft_remove_first_env(t_control *control);

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

void		add_index(t_element *elem);

char	*ft_get_parsed_env(char *str);

int			ft_init_list(t_control *list, char **envp);

		// FT_LINKED_LISTS 2

t_element	*ft_init(void);

void	ft_deal_SHLVL(t_control *control);

		//	FREE GARBAGE COLLECTOR

void		free_all(t_control *control);

void		free_elms(t_element *first);

		//	FT_MANAGE_FDS.C

int		*ft_manage_fds(char ***newargv, char **paths, int **fds);

int		check_ret_stdin(int *ret);

int		check_ret_stdout(int *ret);

		//	FT_CHILD.C

int		ft_child(char ***newargv, char **paths, t_control *list, int **fds);

char	**ft_get_envs_var(t_control *list);

		//	FT_UNSET.C
void	ft_replace_str(t_element *tmp);

int		ft_unset(t_control *control, char **newargv);

int		ft_print_stuff(t_element *first, char *str);

t_element	*ft_good_find_in_list(t_element *first, char *noequal_str);

		//	TOOLS2.C

char	*ft_remove_simple_quotes(char *str);

t_bool	is_quest(char *str);

int		ft_is_space_before_qual(char *str);

void	ft_remove_env(t_control *list);

char	*ft_get_dollar_var(char *str, t_control *list);

int		ft_check_position(char c, char c2, char *str);

		//	TOOLS3.C

char	*get_new_line_cmd(char *str, int i, int size, char *str_good);

t_bool	ft_bad_entries(char *str);

		//	ft_clear.c

int		ft_clear(char **newargv);

int		is_OptionOfClear(char **newargv);

		//	TOOLS4.C

void	ft_delete_last(t_element *first);

void	ft_remove_from_env(t_element *to_supp, t_control *control);

char	*get_new_str(char *str, int i, int *size);

void	ft_is_dollar(char **str, t_control *control);

		//	FT_EXIT.C

int		ft_exit(char **arg);

#endif
