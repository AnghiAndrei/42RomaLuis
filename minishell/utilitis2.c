/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/04 16:27:52 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *rule)
{
	char	*line;
	int		fd;

	fd = open("aanghi_temp_file.txt", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("Marshal: Temp file error");
		return ;
	}
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, rule, ft_strlen(rule)) != 0)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	dup2(controll_file("aanghi_temp_file.txt", 1), STDIN_FILENO);
	if (access("aanghi_temp_file.txt", R_OK) == 0)
		unlink("aanghi_temp_file.txt");
}

char	**copy_m(char **m)
{
	char	**cm;
	int		i;

	i = 0;
	cm = malloc((ft_mlen(m) + 1) * sizeof(char *));
	while (m[i] != NULL)
	{
		cm[i] = ft_strjoin(m[i], "\0");
		i++;
	}
	cm[i] = NULL;
	return (cm);
}

int	free_all_steoridi(t_master *master)
{
	free_all(master);
	rl_clear_history();
	free_matrix(master->env);
	return (0);
}

bool	free_n(char *str)
{
	free(str);
	return (true);
}

char	*get_path(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strjoin(cwd, "\0"));
	else
	{
		perror("Marshal: getcwd() error");
	}
	return (ft_strjoin("\0", "\0"));
}
