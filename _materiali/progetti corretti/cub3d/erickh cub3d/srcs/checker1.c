/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:44:59 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/23 00:37:58 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_spaces_inside_map(t_map *textures, int i, int j)
{
	if ((textures->world_map[i - 1][j - 1] != WALL
		&& textures->world_map[i - 1][j - 1] != SPACE)
		|| (textures->world_map[i - 1][j] != WALL
		&& textures->world_map[i - 1][j] != SPACE)
		|| (textures->world_map[i - 1][j + 1] != WALL
		&& textures->world_map[i - 1][j + 1] != SPACE)
		|| (textures->world_map[i][j - 1] != WALL
		&& textures->world_map[i][j - 1] != SPACE)
		|| (textures->world_map[i][j + 1] != WALL
		&& textures->world_map[i][j + 1] != SPACE)
		|| (textures->world_map[i + 1][j - 1] != WALL
		&& textures->world_map[i + 1][j - 1] != SPACE)
		|| (textures->world_map[i + 1][j] != WALL
		&& textures->world_map[i + 1][j] != SPACE)
		|| (textures->world_map[i + 1][j + 1] != WALL
		&& textures->world_map[i + 1][j + 1] != SPACE))
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}

static int	exec_checkers_inside_map(t_map *textures, int i, int j)
{
	if (textures->world_map[i][j] == SPACE)
		return (check_spaces_inside_map(textures, i, j));
	if (!check_doors(textures, i, j))
		return (0);
	return (1);
}

static int	checkers(t_map *textures, int i, int j)
{
	if (i == 0 && j == 0)
		return (check_angle1(textures, i, j));
	else if (i == 0
		&& j == (ft_strlen(textures->world_map[i]) - 1))
		return (check_angle2(textures, i, j));
	else if (!textures->world_map[i + 1] && j == 0)
		return (check_angle3(textures, i, j));
	else if (!textures->world_map[i + 1]
		&& j == (ft_strlen(textures->world_map[i]) - 1))
		return (check_angle4(textures, i, j));
	else if (i == 0)
		return (check_border1(textures, i, j));
	else if (j == 0)
		return (check_border2(textures, i, j));
	else if (!textures->world_map[i + 1])
		return (check_border3(textures, i, j));
	else if (j == (ft_strlen(textures->world_map[i]) - 1))
		return (check_border4(textures, i, j));
	else
		return (exec_checkers_inside_map(textures, i, j));
	return (1);
}

static int	exec_checker(t_map *textures, int i, int j)
{
	int	old_x;
	int	old_y;

	old_x = textures->spawn_x;
	old_y = textures->spawn_y;
	get_spawn_position(textures, i, j);
	if (old_x != -1 && old_y != -1
		&& (old_x != textures->spawn_x || old_y != textures->spawn_y))
		return (print_error("Wrong File. Map is invalid"));
	if (textures->world_map[i][j] == SPACE
		|| textures->world_map[i][j] == DOOR0)
		if (!checkers(textures, i, j))
			return (0);
	return (1);
}

int	check_map(char *line, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
		if (line[i] != WALL && line[i] != SPACE)
			return (print_error("Wrong File. Map is invalid"));
	free(line);
	if (!check_map_content(map))
		return (0);
	i = 0;
	while (map->world_map[i])
	{
		j = 0;
		while (map->world_map[i][j])
			if (!exec_checker(map, i, j++))
				return (0);
		i++;
	}
	set_max_positions(map);
	if (map->max_y < 3 || (map->spawn_x == -1 && map->spawn_y == -1))
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}
