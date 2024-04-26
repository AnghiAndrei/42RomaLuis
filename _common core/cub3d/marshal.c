/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/26 15:47:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ceck_file(char *file)
{
	char	**p;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nMarshal: File not found / unreadable\n", 44));
	p = ft_split(file, '.');
	i = 0;
	while (p[i + 1] != NULL)
		i++;
	if (!(ft_strncmp(p[i], "cub", 3) == 0
			&& ft_strncmp(file, "cub", 4) != 0))
		return (free_matrix(p),
			write(2, "Error\nMarshal: File extension not .cub\n", 39));
	free_matrix(p);
	return (0);
}

static void	supp_marshal(t_master *m, int i, int i2)
{
	m->yp = i + 0.01;
	m->xp = i2 + 0.01;
	m->myp = i;
	m->mxp = i2;
}

static int	ceck_map1(t_master *m, int i, int i2)
{
	while (m->map[++i] != NULL)
	{
		i2 = -1;
		while (m->map[i][++i2] != '\0')
		{
			if (m->map[i][i2] != ' ' && m->map[i][i2] != '1'
				&& m->map[i][i2] != '0'
				&& m->map[i][i2] != 'N' && m->map[i][i2] != 'S'
				&& m->map[i][i2] != 'E' && m->map[i][i2] != 'W')
				return (printf("Error\nMarshal: Found a strange character\n"));
			if ((m->yp != 0 && m->xp != 0)
				&& (m->map[i][i2] == 'N' || m->map[i][i2] == 'S'
				|| m->map[i][i2] == 'E' || m->map[i][i2] == 'W'))
				return (printf("Error\nMarshal: Found another char player\n"));
			else if ((m->yp == 0 && m->xp == 0)
				&& (m->map[i][i2] == 'N' || m->map[i][i2] == 'S'
				|| m->map[i][i2] == 'E' || m->map[i][i2] == 'W'))
				supp_marshal(m, i, i2);
		}
	}
	return (0);
}

static int	close_map(t_master *m, int y, int x)
{
	while (m->map[y] != NULL)
	{
		x = 0;
		while (m->map[y][x] != '\0')
		{
			if (m->map[y][x] == '0' && (y == 0 || x == 0 || y ==
				ft_mlen(m->map) || x == ft_strlen(m->map[y]) - 1))
				return (-1);
			if (m->map[y][x] == '0' && (m->map[y - 1][x] == ' '
				|| m->map[y + 1][x] == ' ' || m->map[y][x + 1] == ' '
				|| m->map[y][x - 1] == ' '))
				return (-1);
			x++;
		}
		y++;
	}
	return (1);
}

int	ceck_map(t_master *m)
{
	char	**mapc;

	if (ceck_map1(m, -1, 0) != 0)
		return (1);
	if (m->yp == 0 && m->xp == 0)
		return (printf("Error\nMarshal: Player not found\n"));
	game_init5(m);
	m->sp = 1;
	if (m->map[(int)(m->yp)][(int)(m->xp)] == 'W'
		|| m->map[(int)(m->yp)][(int)(m->xp)] == 'E')
		m->sp = -1;
	m->map[(int)(m->yp)][(int)(m->xp)] = '0';
	mapc = copy_m(m->map);
	if (close_map(m, 0, 0) == -1)
	{
		free_matrix(mapc);
		return (printf("Error\nMarshal: Invalid map\n"));
	}
	return (free_matrix(mapc), 0);
}
