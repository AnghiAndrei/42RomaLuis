/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/16 11:00:06 by aanghi           ###   ########.fr       */
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

static int	ceck_map1(t_master *m, int i, int i2)
{
	while (m->map[++i] != NULL)
	{
		i2 = -1;
		while (m->map[i][++i2] != '\0')
		{
			printf("%c", m->map[i][i2]);
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
			{
				m->yp = i;
				m->xp = i2;
			}
		}
		printf("\n");
	}
	return (0);
}

static void	blood_fill(char **map, int l, int c, t_point cur)
{
	if (cur.l < 0 || cur.l >= l || cur.c < 0 || cur.c >= c
		|| map[cur.l][cur.c] == '1' || map[cur.l][cur.c] == '-')
		return ;
	if (map[cur.l][cur.c] == ' ')
	{
		map[cur.l][cur.c] = 'X';
		return ;
	}
	if (map[cur.l][cur.c] == '\0')
	{
		map[cur.l][cur.c - 1] = 'X';
		return ;
	}
	map[cur.l][cur.c] = '-';
	blood_fill(map, l, c, (t_point){cur.l - 1, cur.c});
	blood_fill(map, l, c, (t_point){cur.l + 1, cur.c});
	blood_fill(map, l, c, (t_point){cur.l, cur.c - 1});
	blood_fill(map, l, c, (t_point){cur.l, cur.c + 1});
}

int	ceck_map(t_master *m)
{
	char	**mapc;
	t_point	point;

	if (ceck_map1(m, -1, 0) != 0)
		return (free_all(m), 1);
	if (m->yp == 0 && m->xp == 0)
		return (free_all(m), printf("Error\nMarshal: Player not found\n"));
	point.l = m->yp;
	point.c = m->xp;
	mapc = copy_m(m->map);
	blood_fill(mapc, ft_mlen(mapc), ft_strlen(mapc[0]) - 1, point);
	if (pos_line(mapc, 'X') == -1)
	{
		free_matrix(mapc);
		return (free_all(m), printf("Error\nMarshal: Map not close\n"));
	}
	return (free_matrix(mapc), 0);
}
