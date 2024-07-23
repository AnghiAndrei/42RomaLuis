/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:47:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 13:53:21 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count(char *line, char c)
{
	int	i;

	i = 0;
	while (*line != '\0')
	{
		if (*line == c)
			i++;
		line++;
	}
	return (i);
}

void	ceck_format(char *line, int i, int n_line)
{
	if (i == 0 || i + 1 == n_line)
	{
		while (*line != '\n' && *line != '\0')
		{
			if (*line != '1')
			{
				perror("Error\nMarsal: Invalid wall");
				exit(EXIT_FAILURE);
			}
			line++;
		}
	}
	else
	{
		if (line[0] != '1' && line[ft_strlen(line) - 2] != '1')
		{
			perror("Error\nMarsal: Invalid wall");
			exit(EXIT_FAILURE);
		}
	}
}

void	ceck_obj(int p, int e, int c)
{
	if (p != 1)
	{
		perror("Error\nMarsal: Found too many player/no one");
		exit(EXIT_FAILURE);
	}
	if (e != 1)
	{
		perror("Error\nMarsal: Found too many doors/no one");
		exit(EXIT_FAILURE);
	}
	if (c <= 0)
	{
		perror("Error\nMarsal: Not found enough collectibles");
		exit(EXIT_FAILURE);
	}
}

void	malloc_matrix_controll(char **matrix)
{
	if (matrix == NULL)
	{
		perror("Error\nMarshal: Malloc error");
		exit(EXIT_FAILURE);
	}
}

void	ceck_path(int n_line, int fd, int e, int c)
{
	char	**map;
	t_point	p_plaeyr;
	t_point	p_current;
	int		i;

	map = get_matrix_marshal(n_line, fd);
	p_plaeyr.l = pos_line(map, 'P');
	p_plaeyr.c = pos_col(p_plaeyr.l, map, 'P');
	p_current.l = p_plaeyr.l;
	p_current.c = p_plaeyr.c;
	convert_element(map, n_line - 1, ft_strlen(map[0]) - 1, p_current);
	i = 0;
	while (map[i] != NULL)
	{
		e += count(map[i], 'E');
		c += count(map[i], 'C');
		i++;
	}
	if (c != 0 || e != 0)
	{
		perror("Error\nMarshal: No valid path to win");
		exit(EXIT_FAILURE);
	}
}
