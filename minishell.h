/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:44:17 by abrun             #+#    #+#             */
/*   Updated: 2022/01/11 17:57:21 by edjavid          ###   ########.fr       */
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
# include <dirent.h>

		//	MACROS
# define FAILURE 1
# define SUCCESS 0
# define PINK "\033[95m"
# define END "\033[0m"
# define YELLOW "\033[93m"
# define RED "\033[91m"

extern int	g_status;

# define DEAL_EXPORT 1
# define DEAL_ENV 0
# define NEO_ENV 2

		// STRUCTURES
typedef enum s_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef struct s_element
{
	char				*str;
	char				*var_name;
	int					index;
	struct s_element	*next;
}		t_element;

typedef struct s_control
{
	t_element	*first_env;
	t_element	*first_export;
	t_element	*first_env_var;
	int			size;
}		t_control;

		//	MINISHELL.C

void		ft_minishell(t_control *list);

void		sigint_handler(int sig);

void		free_1(char *cmd_line, char **paths, char **env);

		//	INIT_PATHS.C

char		**init_paths(char **envp);

char		**fill_paths(char *line, int count);

int			get_path_len(char *line, int count);

char		*ft_add_one_path(char *line, int *count);

char		*init_param_path(char *envp, int count, int *path_len, int *n);

		//	EXEC_CMD.C

int			exec_cmd(char *cmd_line, char **paths, t_control *list);

char		*get_new_line(char *cmd_line, t_control *list, int *i);

char		*init_cmd_path(char *cmd, char **paths);

char		*init_cmd_with_path(char *cmd, char *path, size_t cmd_len);

void		free_newargv(char ***matc);

		//	EXEC_CMD.C

int			n_pid(char ***newargv);

int			exit_exec(int ret, char ***newargv, char *cmd_line);

		//	PROMPT_MSG.C

char		*prompt_msg(int *ret);

		//	FT_BUILTINS.C

int			ft_builtins(char **newargv, t_control *list, int fd);

int		exec_builtins(char **newargv, t_control *list, char **paths);

int			is_builtins(char *newargv);

		//	FT_ECHO.C

int			ft_echo(char **newargv, int fd);

void		write_newargv(char **newargv, int c, int fd);

int			check_echo_arg(char *newargv);

		//	FT_PWD.C

int			ft_pwd(int fd);

		//	FT_CD.C

int			ft_cd(char **newargv, t_control *list);

int			ft_cd_2(char **newargv, t_control *list);

		//	FT_CD2.C

int			modify_both(t_control *list, char *old_path, char *pwd, int ret);

int			ft_modify_pwd(t_control *list, char *path, char *pwd, int type);

char		*get_var_value(char *var_val);

char		*get_absolute_path(void);

void		deal_old_path(int *ret, char *old_path);

char		*alloc_values(char *path, t_control *list, int type);

		//	FT_CD3.C

int			ft_cd3(char **newargv, char *old_path, int *ret, t_control *list);

int			free_cur(char *cur);

		//	FT_CMD.C

int			ft_cmd(char ***newargv, char **paths, t_control *list, int n_pid);

int			**init_fds(int n_cmd);

int			status_free(int **fds);

int			get_n_cmd(char *cmd_line);

int			n_pid(char ***newargv);

		//	INIT_NEWARGV.C

char		***init_newargv(char *cmd_line, char **paths);

char		***init_param_in(char ***split, char *cmd_line,
				int *c_1, int *c_spl);

int			ft_splen(char **split, int c_spl);

char		***free_init_new(char ***newargv, char **split);

int			is_syntax_er_spl(char **split);

		//	TOOLS.C

t_element	*check_in_list(t_element *first, char *str);

void		ft_dup2(int newfd, int oldfd);

void		ft_close_fd(int fd);

char		*ft_get_good_str(char *str);

char		*ft_is_dollar2(char *str, t_control *control,
				int is_mal, int count);

int			no_unpair_char_before(char *str, int i, char c);

t_element	*ft_is_in_list(t_control *list, char *str);

t_element	*check_in_list(t_element *first, char *str);

		//	TOOLS6.C

int			count_amout(char *str, char c);

char		*ft_is_dollar3(t_control *control, char *new_str, int *is_mal);

void		ft_get_value(t_element *prev1, t_element *prev2, t_element *node2,
				t_element *node1);

t_element	*modify_value(t_element *node1, t_element *node2,
				t_element *prev1, t_element *prev2);

int			add_beg(t_control *list, char *str);

		// FT_ASCII_ORDER.C

t_element	*swap_elem(int pos1, int pos2, t_control *list, int i);

t_bool		is_ascii_ordered(char *str1, char *str2);

		// FT_ASCII_ORDER2.C

t_bool		check_order(t_control *list);

int			order_ascii(t_control *list);

		// EXPORT.C

int			ft_export(t_control *list, char **newargv);

int			add_end_list(char *str, t_element *first, int type);

char		*add_var_name(char *str);

char		*add_str2(char *str, int type);

char		*ft_remove_quotes(char *str);

void		ft_add_new_var(t_control *list, int type);

void		ft_remove_first_env(t_control *control);

		// EXPORT2.C

void		ft_print_export(t_element *first, t_bool bool);

int			ft_get_new_var(t_control *list, char **newargv);

		// EXPORT3.C

int			add_end_list(char *str, t_element *first, int type);

char		*add_str2(char *str, int type);

int			ft_assign(t_element *tmp, t_control *list, char *retreat, int i);

		// EXPORT4.C

int			get_f(t_control *list, char *var_name, char *retreat);

		// EXPORT5.C

int			process_retreat(char *newargv, char *retreat);

int			ft_get_new_var(t_control *list, char **newargv);

int			get_tmp(char *retreat, t_element *tmp,
				t_control *list, char *var_name);

void		mdval(t_element *elem, char *str, int type);

		// FT_ENV.C

int			ft_env(t_control *list);

		//	FT_READ_INPUT.C

int			ft_read_input(char ***newargv, char **paths);

char		**init_files(char **newargv, int *c);

int			init_config(char **newargv, int *c);

		//	MAKE_CONFIGS_RDIN.C

int			make_configs_rdin(char ***newargv, char **files,
				char **heredoc, int *c);

int			make_config_1(char **heredoc, char *lim, int *last);

int			make_config_2(char **files, char *arg, int *last);

char		*get_heredoc(char *lim);

char		*print_error_rdin(int ret, char *lim, char *heredoc);

		//	GET_NEWARGV_RDIN.C

char		**get_newargv_rdin(char **newargv, int c, char **paths);

char		**add_one_arg_rdin(char **newargv, char **new,
				char **paths, int *counter);

char		*ft_strdup_rdin(char *s, char **mat1, char **mat2);

		//	RETURNS_RDIN.C

int			dup_readin(char ***files, char **heredoc, int last);

int			dup_readin_2(char **heredoc, char ***files, int last, int fdin);

int			exit_readin(char **files, char *heredoc, int ret);

		//	FT_REDIRECTION.C

int			*ft_redirection(char ***newargv, int *ret, int forked);

char		***loop_redirection(char ***newargv, int *ret, int c, int forked);

int			which_redirection(char *s);

int			get_outfd(char *file, int config);

int			get_outfd_2(char *file, int config);

		//	FT_REDIRECTION_UTILS.C

char		**get_new_redir(char **newargv, int redir);

char		**free_redirection(char **newargv, char **new);

int			*assign_config(int *ret, int config, int fd);

int			*exit_redirection(int *box, int *ret);

int			is_other_redin(char **newargv);

int			is_other_wrout(char **newargv);

char		***exit_fd_neg(int *box, char ***newargv);

		// FT_LINKED_LISTS

void		ft_remove_from_list(t_element *to_supp, t_element *first);

t_element	*elem_in_list(t_element *first, char *str);

char		*is_in_list(t_element *first, char *str);

void		add_index(t_element *elem);

char		*ft_get_parsed_env(char *str);

int			ft_init_list(t_control *list, char **envp);

		// FT_LINKED_LISTS 2

t_element	*ft_init(void);

void		ft_deal_shlvl(t_control *control);

		//	FREE GARBAGE COLLECTOR

void		free_elm(t_element *tmp);

void		free_all(t_control *control);

void		free_elms(t_element *first);

		//	FT_MANAGE_FDS.C

int			*ft_manage_fds(char ***newargv, char **paths,
				int **fds, int forked);

void		free_manage_fds(int *ret, char ***newargv);

int			*init_ret(void);

		//	FT_CHILD.C

int			ft_child(char ***newargv, char **paths, t_control *list, int **fds);

void		is_directory(char *arg);

char		**ft_get_envs_var(t_control *list);

		//	FT_UNSET.C

void		ft_replace_str(t_element *tmp);

int			ft_unset(t_control *control, char **newargv);

int			ft_print_stuff(t_element *first, char *str);

t_element	*ft_good_find_in_list(t_element *first, char *noequal_str);

		//	TOOLS2.C

char		*add_value_name(char *str);

char		*ft_remove_simple_quotes(char *str);

t_bool		is_quest(char *str);

int			ft_is_space_before_qual(char *str);

void		ft_remove_env(t_control *list);

char		*ft_get_dollar_var(char *str, t_control *list);

int			ft_check_position(char c, char c2, char *str);

		//	TOOLS3.C

int			no_unpair_char_before(char *str, int i, char c);

char		*get_new_line_cmd(char *str, int i, int size, char *str_good);

t_bool		ft_bad_entries(char **str);

t_bool		ft_str_bad_entry(char *str);

t_bool		is_surrounded(char *str, size_t size, char c);

		//	ft_clear.c

int			ft_clear(char **newargv);

int			is_option_of_clear(char **newargv);

		//	TOOLS4.C

void		ft_remove_new_vars_from_lists(t_control *list);

void		ft_delete_last(t_element *first);

void		ft_remove_from_env(t_element *to_supp, t_control *control);

char		*get_new_str(char *str, int i, int *size);

void		ft_is_dollar(char **str, t_control *control);

		//	TOOLS5.C

void		ft_delete_last(t_element *first);

int			ft_is_space_before_qual(char *str);

char		*ft_deal_space(char *str);

char		*ft_get_dollar_var(char *str, t_control *list);

void		ft_remove_from_list(t_element *to_supp, t_element *first);

		//	FT_EXIT.C

int			ft_exit(char **arg);

int			ft_exit_2(char **arg);

		//	FT_CLOSE_FDS.C

void		ft_close_fds(int **fds, int n);

void		ft_close_fds_around(int **fds, int n);

		//	CHECK_RDS.C

int			check_rds(char *cmd);

int			rds_ok(char *cmd, int c, char k);
#endif
