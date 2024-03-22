/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:45:18 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/06 09:29:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ricerca_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	perror("Marshal: Environment variable not found");
	exit(EXIT_FAILURE);
}

char	*program_name(char *command, char *path)
{
	char	**c_c;
	char	**path_c;
	int		i;

	i = 0;
	c_c = ft_split((const char *)command, ' ');
	path_c = ft_split((const char *)path, ':');
	while (path_c[i] != NULL)
	{
		if (access(ft_strjoin(ft_strjoin(path_c[i], "/"), c_c[0]), R_OK) == 0)
			return (ft_strjoin(ft_strjoin(path_c[i], "/"), c_c[0]));
		i++;
	}
	perror("Marshal: Command not found");
	exit(EXIT_FAILURE);
}

void	here_doc(char *rule)
{
	char	*line;
	int		fd;

	fd = open("aanghi_temp_file.txt", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("Marshal: Temp file error");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, rule, ft_strlen(rule)) != 0)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	dup2(controll_in("aanghi_temp_file.txt"), STDIN_FILENO);
	if (access("aanghi_temp_file.txt", R_OK) == 0)
		unlink("aanghi_temp_file.txt");
}
