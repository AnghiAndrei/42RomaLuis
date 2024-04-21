/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_angles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:34:45 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/19 11:16:34 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_angle1(t_map *textures, int i, int j)
{
	if ((textures->world_map[i][j + 1] != WALL
		&& textures->world_map[i][j + 1] != SPACE)
		|| (textures->world_map[i + 1][j] != WALL
		&& textures->world_map[i + 1][j] != SPACE)
		|| (textures->world_map[i + 1][j + 1] != WALL
		&& textures->world_map[i + 1][j + 1] != SPACE)
		|| textures->world_map[i][j] == DOOR0)
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}

int	check_angle2(t_map *textures, int i, int j)
{
	if ((textures->world_map[i][j - 1] != WALL
		&& textures->world_map[i][j - 1] != SPACE)
		|| (textures->world_map[i + 1][j - 1] != WALL
		&& textures->world_map[i + 1][j - 1] != SPACE)
		|| (textures->world_map[i + 1][j] != WALL
		&& textures->world_map[i + 1][j] != SPACE)
		|| textures->world_map[i][j] == DOOR0)
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}

int	check_angle3(t_map *textures, int i, int j)
{
	if ((textures->world_map[i - 1][j] != WALL
		&& textures->world_map[i - 1][j] != SPACE)
		|| (textures->world_map[i - 1][j + 1] != WALL
		&& textures->world_map[i - 1][j + 1] != SPACE)
		|| (textures->world_map[i][j + 1] != WALL
		&& textures->world_map[i][j + 1] != SPACE)
		|| textures->world_map[i][j] == DOOR0)
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}

int	check_angle4(t_map *textures, int i, int j)
{
	if ((textures->world_map[i - 1][j - 1] != WALL
		&& textures->world_map[i - 1][j - 1] != SPACE)
		|| (textures->world_map[i - 1][j] != WALL
		&& textures->world_map[i - 1][j] != SPACE)
		|| (textures->world_map[i][j - 1] != WALL
		&& textures->world_map[i][j - 1] != SPACE)
		|| textures->world_map[i][j] == DOOR0)
		return (print_error("Wrong File. Map is invalid"));
	return (1);
}
