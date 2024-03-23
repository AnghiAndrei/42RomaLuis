/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:42:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/22 12:41:37 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipe(t_master *master, t_cmd *cur, int status, pid_t pid)
{
	int		fd[2];

	ceck_pipe_fork(fd, &pid);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (controll_builtins(master, cur) == 0)
		{
			execve(program_name(cur->cmd, master->path),
				get_args(cur->cmd, master, cur), master->env);
			write(2, "02: What command did you give me, darling\n", 42);
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_code_exit = WEXITSTATUS(status);
	}
}

static void	child(t_master *master, t_cmd *cur)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (controll_builtins(master, cur) == 0)
		{
			execve(program_name(cur->cmd, master->path),
				get_args(cur->cmd, master, cur), master->env);
			write(2, "02: What command did you give me, darling\n", 42);
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_code_exit = WEXITSTATUS(status);
	}
}

static void	builtin_dad(t_master *master, t_cmd *cur, char *str, int s)
{
	master->print = s;
	if (ft_strncmp(str, "export", 7) == 0)
		bt_export(master, cur, -1);
	if (ft_strncmp(str, "unset", 6) == 0)
		bt_unset(master, cur, -1);
}

static void	pipe_cmd(t_master *master, t_cmd *cur)
{
	builtin_dad(master, cur, clear_space(cur->cmd), 0);
	if (!(cur->or == 1 && g_code_exit != 0))
	{
		if (cur->pipe == 1)
			child_pipe(master, cur, 0, 0);
		else
			child(master, cur);
	}
	if (cur->pipe == 2)
	{
		dup2(master->in, STDIN_FILENO);
		dup2(master->out, STDOUT_FILENO);
	}
	cur = cur->next;
}

void	executor(t_master *master, int i)
{
	t_cmd	*cur;

	cur = master->lcmd;
	if (master->ncmd == 1 && ft_strncmp(clear_space(cur->cmd),
			"exit", 5) == 0)
		bt_exit(cur->cmd);
	if (master->npipe == 0)
	{
		while (master->ncmd != i++)
		{
			builtin_dad(master, cur, clear_space(cur->cmd), 1);
			if (!(cur->or == 1 && g_code_exit != 0))
				child(master, cur);
			cur = cur->next;
			dup2(master->in, STDIN_FILENO);
			dup2(master->out, STDOUT_FILENO);
		}
	}
	else
	{
		while (master->ncmd != i++)
			pipe_cmd(master, cur);
	}
}
