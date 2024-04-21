/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:49:52 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/20 19:45:03 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_doors(t_map *textures, int i, int j)
{
	if (textures->world_map[i][j] == DOOR0)
	{
		textures->n_doors++;
		if ((!(textures->world_map[i - 1][j] == WALL
				&& textures->world_map[i + 1][j] == WALL)
				&& !(textures->world_map[i][j - 1] == WALL
				&& textures->world_map[i][j + 1] == WALL))
				|| textures->world_map[i + 1][j] == DOOR0
				|| textures->world_map[i][j + 1] == DOOR0
				|| textures->world_map[i - 1][j] == DOOR0
				|| textures->world_map[i][j - 1] == DOOR0)
			return (print_error("Wrong File. Map is invalid"));
	}
	return (1);
}

int	check_map_content(t_map	*textures)
{
	int	i;
	int	j;

	i = 0;
	while (textures->world_map[i])
	{
		j = 0;
		while (textures->world_map[i][j])
		{
			if (textures->world_map[i][j] != WALL
				&& textures->world_map[i][j] != EMPTY
				&& textures->world_map[i][j] != NORD
				&& textures->world_map[i][j] != SOUTH
				&& textures->world_map[i][j] != WEST
				&& textures->world_map[i][j] != EAST
				&& textures->world_map[i][j] != SPACE
				&& textures->world_map[i][j] != DOOR0)
				return (print_error("Wrong File. Map is invalid"));
			j++;
		}
		i++;
	}
	return (1);
}

int	check_textures(t_map *textures)
{
	if (!textures->no || !textures->so || !textures->we || !textures->ea
		|| !textures->str_floor || !textures->str_ceilling)
		return (print_error("Wrong File. Wrong format information"));
	if (!str_to_color(textures->str_floor, &textures->floor)
		|| !str_to_color(textures->str_ceilling, &textures->ceilling))
		return (print_error("Wrong File. Wrong format information"));
	return (1);
}

int	check_params(int argc, char **argv, int *fd)
{
	if (argc != 2)
		return (print_error("Wrong Number of Arguments"));
	if (argv[1][ft_strlen(argv[1]) - 4] != '.'
		|| argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u'
		|| argv[1][ft_strlen(argv[1]) - 1] != 'b')
		return (print_error("Wrong Type of File. It bust be '.cub'"));
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
		return (print_error("Wrong Path. File doesn't exist"));
	return (1);
}
