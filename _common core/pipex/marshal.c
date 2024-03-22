/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:34:23 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 13:06:11 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	controll1(int *fd, pid_t *pid)
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

void	controll2(char **m)
{
	if (m == NULL)
	{
		perror("Marshal: Malloc error");
		exit(EXIT_FAILURE);
	}
}

int	controll_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Marshal: Input file open error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	controll_out(char *file, char *here_doc)
{
	int		fd;

	if (ft_strncmp(here_doc, "here_doc", 8) == 0)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		perror("Marshal: Output file open error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
