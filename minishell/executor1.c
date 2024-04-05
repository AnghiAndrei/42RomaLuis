/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:42:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/04 18:01:44 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_op(t_master *master, t_cmd *cur)
{
	char	*program_name_str;
	char	**args;

	signal(SIGQUIT, sigbs);
	g_code_exit = 269;
	if (controll_builtins(master, cur) == 0)
	{
		program_name_str = program_name(cur->cmd, get_env(master, "PATH"));
		args = get_args(cur->cmd, master, cur);
		if (program_name_str != NULL && cmmal(args) == 1)
			execve(program_name_str, args, master->env);
		free(program_name_str);
		free_matrix(args);
		g_code_exit = 127;
		exit(write(2, STRERROR, 43) + 84);
	}
	else
		exit(free_all_steoridi(master));
}
