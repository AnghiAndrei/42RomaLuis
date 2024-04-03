/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:52:58 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/03 17:17:06 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmmal(char **m)
{
	if (m == NULL)
	{
		return (0);
		perror("Marshal: Malloc error");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ceck_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Marshal: Fork error");
		return (-1);
	}
	return (pid);
}

int	controll_file(char *file, int command)
{
	int		fd;

	fd = -1;
	if (command == 1)
		fd = open(file, O_RDONLY);
	else if (command == 3)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (command == 4)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("Marshal: Input file open error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_pipe_fork(int *fd, pid_t *pid)
{
	if (pipe(fd) == -1)
	{
		perror("Marshal: Pipe error");
		exit(EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("Marshal: Fork error");
		exit(EXIT_FAILURE);
	}
}
