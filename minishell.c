/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:31:49 by abrun             #+#    #+#             */
/*   Updated: 2021/11/23 09:41:50 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status = 0;

int	main(int ac, char **av, char **envp)
{
	char			**paths;
	t_control  	 	*list;
	int				i;

	(void)av;
	if (ac != 1)
		return (1);
	list = ft_init();
	if (!list)
		return (-1);
	i = -1;
	while (envp[++i])
		add_end_list(envp[i], list);	
	paths = init_paths(envp); 
	ft_minishell(paths, list);
	free_matc(paths);
	return (status);
}

void	ft_minishell(char **paths, t_control *list)
{
	char			*cmd_line;
	struct sigaction	sa;
	int				ret;

	ret = 1;
	sa.sa_handler = signal_handler;
	while (ret || cmd_line)
	{
		cmd_line = prompt_msg();
		if (sigaction(SIGINT, &sa, NULL) < 0)
		{
			ft_printf_fd(2, "Sigaction failed\n");
			status = 3;
			return ;
		}
		if (cmd_line)
		{
			exec_cmd(cmd_line, paths, list);
			free(cmd_line);
		}
		if (ret)
			ret = 0;
	}
}

void	signal_handler(int sig)
{
	int	stop;

	(void)sig;
//	while (waitpid(-1, &status, WUNTRACED) > 0);
	ft_printf_fd(2, "status_handler : %d\n", WEXITSTATUS(status));
	stop = WIFSIGNALED(status);
	if (!stop)
	{
		ft_printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	status = 130;
}
