/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjavid <edjavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 18:41:36 by edjavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status = 0;

int	main(int ac, char **av, char **envp)
{
	char		**paths;
    t_control   list;

	(void)av;
	if (ac != 1)
		return (1);
	if (ft_init_list(&list, envp))
		return (-1);
	paths = init_paths(envp);
	ft_minishell(paths, &list);
	free_matc(paths);
	free_all(&list);
	return (status);
}

void	ft_minishell(char **paths, t_control *list)
{
	char			*cmd_line;
	int				ret;

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	cmd_line = prompt_msg();
	if (cmd_line)
		ret = exec_cmd(cmd_line, paths, list);
	else
		ret = 0;
	while (ret > 0 && cmd_line)
	{
		free(cmd_line);
		cmd_line = prompt_msg();
		if (cmd_line)
			ret = exec_cmd(cmd_line, paths, list);
	}
	if (cmd_line)
		free(cmd_line);
	if (ret < 0)
		ft_printf_fd(2, "Un malloc a echoue !\n");
}

void	sigint_handler(int sig)
{
	int	stat;

	if (sig == 2)
	{
		stat = 0;
		waitpid(-1, &stat, 0);
		if (!stat && status != 9)
		{
			rl_clear_history();
			ft_printf_fd(1, "\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (!stat && status == 9)
		{
			exit(130);
		}
		else
			ft_printf_fd(1, "\n");
		status = 130;
	}
}
