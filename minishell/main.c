/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:09:24 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/04 21:34:00 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_code_exit = 0;

static	void	sigc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	if (g_code_exit != 269)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_code_exit = 130;
	}
	else
		g_code_exit = 1;
}

static void	sigd(int signum)
{
	(void)signum;
	g_code_exit = 130;
	exit(0);
}

void	sigbs(int signum)
{
	(void)signum;
	write(2, " 02: Close 0 input, darling\n", 27);
	exit(131);
}

int	main(int argc, char **argv, char **env)
{
	t_master	m;

	if (argc >= 2 || init_start(&m, env))
		return (write(2, "Marshal: Bro, Why give to 02 a input?\n", 38));
	if (signal(SIGINT, sigc) == SIG_ERR || signal(SIGTERM, sigd) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (printf("Marshal: Signal error"));
	(void)argv;
	while (1)
	{
		m.input = get_command_f_0();
		if (m.input == NULL)
		{
			rl_clear_history();
			return (free_matrix(m.env), 1);
		}
		if ((m.input[0] == ' ' || m.input[0] == '\0') && free_n(m.input))
			continue ;
		m.npipe = count_pipe(m.input, '|');
		split_cmd(&m);
		executor(&m, NULL, 0);
		free_all(&m);
	}
	rl_clear_history();
	return (free_matrix(m.env), 0);
}
