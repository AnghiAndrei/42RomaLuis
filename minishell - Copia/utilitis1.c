/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/21 17:32:55 by aanghi           ###   ########.fr       */
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

void	init_start(t_master *master, char **env)
{
	master->ncmd = 0;
	master->env = env;
	master->lcmd = NULL;
	master->path = getenv("PATH");
	master->out = dup(STDOUT_FILENO);
	master->in = dup(STDIN_FILENO);
}

char	*clear_space(char *str)
{
	int		i;
	int		i2;

	i = skip(0, str);
	i2 = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (ft_substr(str, i2, i - i2));
}

int	ft_mlen(char **m)
{
	int		i;

	i = 0;
	while (m[i] != NULL)
		i++;
	return (i);
}

void	free_matrix(char **m)
{
	int		i;

	i = -1;
	while (m[++i] != NULL)
		free(m[i]);
	free(m);
}
