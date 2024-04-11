/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/10 14:33:59 by aanghi           ###   ########.fr       */
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

int ceck_map1(t_master *master, int i, int i2)
{
	while (master->map[++i] != NULL)
	{
		i2 = -1;
		while (master->map[++i2] != '\0')
		{
			if (master->map[i2] != ' ' || master->map[i2] != '1'
				master->map[i2] != 'N' || master->map[i2] != 'E'
				master->map[i2] != 'E' || master->map[i2] != 'O')
				return (printf("Error\nMarshal: Found a stranghe char"));
			if ((master->yp != 0 && master->xp != 0)
				master->map[i2] == 'N' || master->map[i2] == 'E'
				master->map[i2] == 'E' || master->map[i2] == 'O')
				return (printf("Error\nMarshal: Found anather player char"));
			if ((master->yp == 0 && master->xp == 0)
				master->map[i2] == 'N' || master->map[i2] == 'E'
				master->map[i2] == 'E' || master->map[i2] == 'O')
			{
				master->yp = i;
				master->xp = i2;
			}
		}
	}
	return (0);
}

//possibili soluzioni:
// flood fill su tutta la mappa fermato solo dai muri,
// se pero si ritrova fuori dalla matrice vuol dire che
// non circondato da muri la mappa
int ceck_map(t_master *master, int i, int i2)
{
	if (ceck_map1(master, -1, 0) != 0)
		return (1);
	while (master->map[++i] != NULL)
	{
		i2 = -1;
		while (master->map[++i2] != '\0')
			printf("%c", master->map[i2]);
		printf("\n");
	}
	return (0);
}
