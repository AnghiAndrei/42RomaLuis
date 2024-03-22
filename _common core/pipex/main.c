/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:43:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 13:07:05 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *cmd, char *path)
{
	int		fd[2];
	pid_t	pid;

	controll1(fd, &pid);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(program_name(cmd, path), get_args(cmd), NULL);
		perror("Marshal: Last command error");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		i;

	if (argc >= 5)
	{
		controll_out(argv[argc - 1], argv[1]);
		i = 3;
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc(argv[2]);
		else
		{
			dup2(controll_in(argv[1]), STDIN_FILENO);
			i = 2;
		}
		while (i != argc - 2)
			child(argv[i++], ricerca_path(envp));
		dup2(controll_out(argv[argc - 1], argv[1]), STDOUT_FILENO);
		cmd = argv[argc - 2];
		execve(program_name(cmd, ricerca_path(envp)), get_args(cmd), NULL);
		perror("Marshal: Last command error");
		exit(EXIT_FAILURE);
	}
	write(1, "Marshal: Not enough arguments", 29);
	return (0);
}
