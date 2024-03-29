/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:09:24 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/28 16:13:54 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_code_exit = 0;

static	void	sigc(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	sigd(int signum)
{
	(void)signum;
	g_code_exit = 0;
	exit(0);
}

static void	sigbs(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("  ", 1);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_master	master;

	if (argc >= 2 || init_start(&master, env))
		return (write(2, "Marshal: Bro, Why give to 02 a input?\n", 38));
	if (signal(SIGINT, sigc) == SIG_ERR || signal(SIGTERM, sigd) == SIG_ERR
		|| signal(SIGQUIT, sigbs) == SIG_ERR)
		return (printf("Marshal: Signal error"));
	(void)argv;
	while (1)
	{
		master.input = get_command_f_0();
		if (master.input == NULL)
		{
			rl_clear_history();
			return (free_matrix(master.env), 1);
		}
		if (master.input[0] == ' ' && master.input[1] == '\0')
			continue ;
		master.npipe = count_pipe(master.input, '|');
		split_cmd(&master);
		executor(&master, NULL, 0);
		free_all(&master);
	}
	rl_clear_history();
	return (free_matrix(master.env), 0);
}
