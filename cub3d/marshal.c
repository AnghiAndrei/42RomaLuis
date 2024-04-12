/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/11 11:59:37 by aanghi           ###   ########.fr       */
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

int	ceck_map1(t_master *m, int i, int i2)
{
	while (m->map[++i] != NULL)
	{
		i2 = -1;
		while (m->map[i][++i2] != '\0')
		{
			if (m->map[i][i2] != ' ' && m->map[i][i2] != '1'
				&& m->map[i][i2] != '0'
				&& m->map[i][i2] != 'N' && m->map[i][i2] != 'S'
				&& m->map[i][i2] != 'E' && m->map[i][i2] != 'O')
				return (printf("Error\nMarshal: Found a stranghe char\n"));
			if ((m->yp != 0 && m->xp != 0)
				|| m->map[i][i2] == 'N' || m->map[i][i2] == 'S'
				|| m->map[i][i2] == 'E' || m->map[i][i2] == 'O')
				return (printf("Error\nMarshal: Found anather player char"));
			if ((m->yp == 0 && m->xp == 0)
				|| m->map[i][i2] == 'N' || m->map[i][i2] == 'S'
				|| m->map[i][i2] == 'E' || m->map[i][i2] == 'O')
			{
				m->yp = i;
				m->xp = i2;
			}
		}
	}
	return (0);
}

//possibili soluzioni:
// flood fill su tutta la mappa fermato solo dai muri,
// se pero si ritrova fuori dalla matrice vuol dire che
// non circondato da muri la mappa
int	ceck_map(t_master *master, int i, int i2)
{
	if (ceck_map1(master, -1, 0) != 0)
		return (1);
	while (master->map[++i] != NULL)
	{
		i2 = -1;
		while (master->map[i][++i2] != '\0')
			printf("%c", master->map[i][i2]);
		printf("\n");
	}
	return (0);
}
