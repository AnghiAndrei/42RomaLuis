/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:42:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/05/09 16:30:46 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_op(t_master *master, t_cmd *cur)
{
	char	*prog_n;
	char	**args;

	signal(SIGQUIT, sigbs);
	if (controll_builtins(master, cur) == 0)
	{
		if (cur->cmd[0] == ' ' && cur->cmd[1] == '\0')
			exit(write(2, STRERROR, 43) + 84);
		prog_n = program_name(cur->cmd, get_env(master, "PATH"));
		args = get_args(cur->cmd, master, cur);
		g_code_exit = 269;
		if (ft_strncmp(prog_n, "o red", 6) == 0 && free_matrix(args) == 0)
			exit(0);
		if (prog_n != NULL)
		{
			execve(prog_n, args, master->env);
			free(prog_n);
		}
		free_matrix(args);
		g_code_exit = 127;
		exit(write(2, STRERROR, 43) + 84);
	}
	else
		exit(free_all_2(master));
}
