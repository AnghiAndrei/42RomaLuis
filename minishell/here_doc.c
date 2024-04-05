/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:56:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 12:58:44 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_child(char *rule)
{
	char	*line;
	int		fd;

	fd = open("aanghi_temp_file.txt", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("Marshal: Temp file error");
		return ;
	}
	line = readline("02(here_doc|): ");
	while (line != NULL && ft_strncmp(line, rule, ft_strlen(rule)) != 0)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("02(here_doc|): ");
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
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(controll_file("aanghi_temp_file.txt", 1), STDIN_FILENO);
		if (access("aanghi_temp_file.txt", R_OK) == 0)
			unlink("aanghi_temp_file.txt");
	}
}
