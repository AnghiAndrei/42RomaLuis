/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:09:24 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 15:09:24 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_code_exit = 0;

int	main(int argc, char **argv, char **env)
{
	t_master	master;

	if (argc >= 2)
		return (write(2, "Marshal: Bro, Why give to 02 a input?\n", 38));
	(void)argv;
	init_start(&master, env);
	while (1)
	{
		master.input = get_command_f_0();
		if (master.input[0] == ' ' && master.input[1] == '\0')
			continue ;
		master.npipe = count_pipe(master.input, '|');
		split_cmd(&master);
		executor(&master, 0);
		free_all(&master);
	}
	return (0);
}
