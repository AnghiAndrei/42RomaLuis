/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:51 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 10:20:08 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_matrix(char *file, int i, int *n_line)
{
	char	**map;
	char	*line;
	int		fd;

	fd = open_file(file);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		(*n_line)++;
	}
	free(line);
	close(fd);
	fd = open_file(file);
	map = malloc((*n_line + 1) * sizeof(char *));
	malloc_matrix_controll(map);
	map[0] = get_next_line(fd);
	while (i != *n_line)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	return (map);
}

int	count_line(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

char	**mod_map(char **map, int l, t_mlx *mlx)
{
	int		i;
	int		b;

	mlx->v = 0;
	i = 1;
	while (i != l - 1)
	{
		b = 1;
		while (map[i][b + 1] != '\0' && map[i][b + 1] != '\n')
		{
			if (map[i][b] == '1')
			{
				if (i * b % 3 == 0)
				{
					mlx->v++;
					map[i][b] = '2';
				}
			}
			b++;
		}
		i++;
	}
	if (mlx->v == 0)
		map[i][b - 1] = '2';
	return (map);
}

void	config_mlx(t_mlx *mlx, char **map)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, (ft_strlen(map[0]) - 1) * 100,
			count_line(map) * 100, "Capodanno a Napoli");
	mlx->map = map;
	mlx->path = mlx_xpm_file_to_image(mlx->mlx, "textures/0.xpm", &mlx->i,
			&mlx->j);
	mlx->wallnov = mlx_xpm_file_to_image(mlx->mlx, "textures/1.xpm", &mlx->i,
			&mlx->j);
	mlx->wallv = mlx_xpm_file_to_image(mlx->mlx, "textures/2.xpm", &mlx->i,
			&mlx->j);
	mlx->bag = mlx_xpm_file_to_image(mlx->mlx, "textures/C.xpm", &mlx->i,
			&mlx->j);
	mlx->player = mlx_xpm_file_to_image(mlx->mlx, "textures/P.xpm", &mlx->i,
			&mlx->j);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "textures/E.xpm", &mlx->i,
			&mlx->j);
	mlx->exit_open = mlx_xpm_file_to_image(mlx->mlx, "textures/F.xpm", &mlx->i,
			&mlx->j);
	mlx->shadow = mlx_xpm_file_to_image(mlx->mlx, "textures/U.xpm", &mlx->i,
			&mlx->j);
	mlx->fire = mlx_xpm_file_to_image(mlx->mlx, "textures/I.xpm", &mlx->i,
			&mlx->j);
	config_mlx2(mlx);
}
