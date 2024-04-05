/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:42:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 02:31:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipe(t_master *master, t_cmd *cur, pid_t pid)
{
	int		fd[2];

	check_pipe_fork(master, cur, fd, &pid);
	if (pid == 0)
	{
		close(fd[0]);
		child_op(master, cur);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
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
		child_op(master, cur);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_code_exit = WEXITSTATUS(status);
	}
}

static void	builtin_dad(t_master *master, t_cmd *cur, char *str)
{
	master->print = 0;
	if (ft_strncmp(str, "export", 7) == 0)
		bt_export(master, cur, (t_data2){NULL, extr_m(cur, 0, 0), NULL, -1});
	if (ft_strncmp(str, "unset", 6) == 0)
		bt_unset(master, cur, -1, extr_m(cur, 0, 0));
	if (ft_strncmp(str, "cd", 3) == 0)
		bt_cd(master, cur, get_env(master, "HOME"),
			get_args(cur->cmd, master, cur));
	master->print = 1;
	free(str);
}

static int	pipe_cmd(t_master *master, t_cmd *cur)
{
	builtin_dad(master, cur, clear_space(cur->cmd));
	if (!(cur->or == 1 && g_code_exit != 0))
	{
		child_pipe(master, cur, 0);
	}
	return (0);
}

void	executor(t_master *master, char *str, int i)
{
	t_cmd	*cur;

	cur = master->lcmd;
	str = clear_space(cur->cmd);
	if (master->ncmd == 1 && ft_strncmp(str, "exit", 5) == 0 && free_n(str))
		bt_exit(master, cur->cmd, get_a(0, cur->cmd), 0);
	free(str);
	while (master->npipe == 0 && master->ncmd != i++)
	{
		builtin_dad(master, cur, clear_space(cur->cmd));
		if (!(cur->or == 1 && g_code_exit != 0))
			child(master, cur);
		cur = cur->next;
		dup2(master->in, STDIN_FILENO);
		dup2(master->out, STDOUT_FILENO);
	}
	while (master->npipe != 0 && master->ncmd != i++
		&& pipe_cmd(master, cur) == 0)
		cur = cur->next;
	while (waitpid(-1, &i, 0) > 0)
		;
	dup2(master->in, STDIN_FILENO);
	dup2(master->out, STDOUT_FILENO);
}
