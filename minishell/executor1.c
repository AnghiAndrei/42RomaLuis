/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:42:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 14:51:40 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_op(t_master *master, t_cmd *cur)
{
	char	*program_name_str;
	char	**args;

	signal(SIGQUIT, sigbs);
	if (controll_builtins(master, cur) == 0)
	{
		if (cur->cmd[0] == ' ' && cur->cmd[1] == '\0')
		{
			program_name_str = program_name(cur->cmd, get_env(master, "PATH"));
			args = get_args(cur->cmd, master, cur);
			g_code_exit = 269;
			if (program_name_str != NULL)
			{
				execve(program_name_str, args, master->env);
				free(program_name_str);
			}
			free_matrix(args);
		}
		g_code_exit = 127;
		exit(write(2, STRERROR, 43) + 84);
	}
	else
		exit(free_all_steoridi(master));
}
