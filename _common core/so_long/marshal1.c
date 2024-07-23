/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:02:32 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 13:47:47 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ceck_file(char *file)
{
	int		fd;
	char	**p;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nMarshal: File not found / unreadable");
		exit(EXIT_FAILURE);
	}
	p = ft_split(file, '.');
	if (!(ft_strncmp(p[sizeof(p) / sizeof(char *)], "ber", 3) == 0
			&& ft_strncmp(file, "ber", 4) != 0))
	{
		perror("Error\nMarshal: File extension not .ber");
		exit(EXIT_FAILURE);
	}
	ceck_map(file);
}

int	open_file(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nMarshal: File not found / unreadable");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	controll_line(char *line, int max_lent)
{
	int		len;

	len = ft_strlen(line) - 1;
	if (line[len] == '\n')
		len--;
	if (len != max_lent)
	{
		perror("Error\nMarshal: Different lengths of the map");
		exit(EXIT_FAILURE);
	}
	while (*line != '\0')
	{
		if (!(*line == '1' || *line == '0' || *line == 'C'
				|| *line == 'E' || *line == 'P' || *line == '\n'))
		{
			perror("Error\nMarshal: Illegal character found in the map");
			exit(EXIT_FAILURE);
		}
		line++;
	}
}

void	ceck_map_deep(int n_line, char *file, int p, int e)
{
	char	*line;
	int		fd;
	int		i;
	int		c;

	c = 0;
	i = 0;
	fd = open_file(file);
	line = get_next_line(fd);
	ceck_map_square(line, n_line);
	while (line != NULL)
	{
		p += count(line, 'P');
		e += count(line, 'E');
		c += count(line, 'C');
		ceck_format(line, i, n_line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	ceck_obj(p, e, c);
	ceck_path(n_line, open_file(file), 0, 0);
}

void	ceck_map(char *file)
{
	char	*line;
	int		max_lent;
	int		fd;
	int		n_line;

	fd = open_file(file);
	line = get_next_line(fd);
	max_lent = ft_strlen(line) - 1;
	n_line = 0;
	if (line[max_lent] == '\n')
		max_lent--;
	while (line != NULL)
	{
		controll_line(line, max_lent);
		free(line);
		line = get_next_line(fd);
		n_line++;
	}
	close(fd);
	ceck_map_deep(n_line, file, 0, 0);
}
