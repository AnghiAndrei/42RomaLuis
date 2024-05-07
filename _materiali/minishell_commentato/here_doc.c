/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:56:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 06:09:45 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_child(char *rule)
{
	char	*line;
	int		fd;

	fd = open("aanghitf.txt", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("Marshal: Temp file error");
		return ;
	}
	while (1)
	{
		write(0, "02[HERE_DOC]: ", 14);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || (ft_strncmp(line, rule, ft_strlen(rule)) == 0
				&& ft_strlen(rule) == ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

static void	sigc2(int signum)
{
	(void)signum;
	g_code_exit = 130;
	exit(g_code_exit);
}

void	here_doc(char *rule)
{
	pid_t	pid;

	pid = ceck_fork();
	if (pid == 0)
	{
		if (signal(SIGINT, sigc2) == SIG_ERR)
			printf("Marshal: Signal error");
		here_doc_child(rule);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(controll_file("aanghitf.txt", 1), STDIN_FILENO);
		if (access("aanghitf.txt", R_OK) == 0)
			unlink("aanghitf.txt");
	}
}
