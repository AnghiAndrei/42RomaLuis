/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:50:52 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/20 20:00:47 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_minimap_square(t_things *things, int x, int y, int color)
{
	int	offset_x;
	int	offset_y;

	offset_x = 0;
	while (offset_x < 10)
	{
		offset_y = 0;
		while (offset_y < 10)
		{
			my_mlx_pixel_put(things->data, x + offset_x, y + offset_y, color);
			offset_y++;
		}
		offset_x++;
	}
}

static void	put_minimap_column(t_things *things, int start_x, int x)
{
	int	start_y;
	int	y;
	int	pix_x;
	int	pix_y;

	start_y = (int) floor(things->pos_y);
	y = start_y - 4;
	pix_x = 50 + ((x - start_x) * 10);
	while (y <= start_y + 4)
	{
		pix_y = 50 + ((start_y - y) * 10);
		if (x < 0 || y < 0 || y >= things->map->max_y
			|| x >= ft_strlen(things->map->world_map[y]))
			put_minimap_square(things, pix_x, pix_y, 0x000335fc);
		else if (x == start_x && y == start_y)
			put_minimap_square(things, pix_x, pix_y, 0x0003fc6b);
		else if (things->map->world_map[y][x] >= DOOR0
			&& things->map->world_map[y][x] <= DOOR9)
			put_minimap_square(things, pix_x, pix_y, 0x00fc0388);
		else if (things->map->world_map[y][x] == WALL)
			put_minimap_square(things, pix_x, pix_y, 0x00FFFFFF);
		else if (things->map->world_map[y][x] != WALL)
			put_minimap_square(things, pix_x, pix_y, 0x00000000);
		y++;
	}
}

void	update_minimap(t_things *things)
{
	int	start_x;
	int	x;

	start_x = (int) floor(things->pos_x);
	x = start_x - 4;
	while (x <= start_x + 4)
	{
		put_minimap_column(things, start_x, x);
		x++;
	}
}
