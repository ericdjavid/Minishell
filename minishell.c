/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2022/01/14 11:24:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_control	list;

	(void)av;
	if (ac != 1)
		return (1);
	if (ft_init_list(&list, envp))
		return (-1);
	ft_minishell(&list);
	free_all(&list);
	return (g_status);
}

void	ft_minishell(t_control *list)
{
	char	*cmd_line;
	int		ret;
	char	**paths;
	char	**env;

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	env = ft_get_envs_var(list);
	paths = init_paths(env);
	cmd_line = prompt_msg(&ret);
	if (cmd_line)
		ret = exec_cmd(cmd_line, paths, list);
	while ((ret > 0 && cmd_line) || ret == -2)
	{
		free_1(cmd_line, paths, env);
		env = ft_get_envs_var(list);
		paths = init_paths(env);
		cmd_line = prompt_msg(&ret);
		if (cmd_line)
			ret = exec_cmd(cmd_line, paths, list);
	}
	if (ret == -1)
		ft_printf_fd(2, RED "minishell: error with a malloc\n" END);
	free_1(cmd_line, paths, env);
}

void	sigint_handler(int sig)
{
	int	stat;

	if (sig == 2)
	{
		stat = 0;
		waitpid(-1, &stat, 0);
		if (!stat && g_status != 9)
		{
			ft_printf_fd(1, "\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (!stat && g_status == 9)
		{
			exit(130);
		}
		else
			ft_printf_fd(1, "\n");
		g_status = 130;
	}
}

void	free_1(char *cmd_line, char **paths, char **env)
{
	if (cmd_line)
		free(cmd_line);
	if (paths)
		free_matc(paths);
	if (env)
		free_matc(env);
}
