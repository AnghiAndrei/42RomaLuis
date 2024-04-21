/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:13:19 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/22 13:38:37 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	raytrace(t_walls_data *data, t_things *things, int i)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (things->map->world_map[data->map_y][data->map_x] == WALL)
			data->hit = 1;
		if (data->map_y == things->map->doors[i].pos.y
			&& data->map_x == things->map->doors[i].pos.x)
			data->hit = 2;
	}
}

static void	setup_info(t_walls_data *data, t_things *things)
{
	data->w_dist = f_t(data->side == 0, data->side_dist_x - data->delta_x,
			data->side_dist_y - data->delta_y);
	data->line_height = (int)(SCREENHEIGHT / data->w_dist);
	data->draw_start = -data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREENHEIGHT / 2;
	data->wall_x = f_t(data->side == 0, things->pos_y + data->w_dist
			* data->ray_dir_y,
			things->pos_x + data->w_dist * data->ray_dir_x);
	if (data->draw_end >= SCREENHEIGHT)
		data->draw_end = SCREENHEIGHT - 1;
}

static void	render_column(t_walls_data *data, t_things *things, int x)
{
	unsigned int	color;
	int				temp;

	data->wall_x -= floor((data->wall_x));
	data->tex_x = (int)(data->wall_x * (double)TEXWIDTH);
	if (data->side == 0 && data->ray_dir_x > 0)
		data->tex_x = TEXWIDTH - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y < 0)
		data->tex_x = TEXWIDTH - data->tex_x - 1;
	data->step = 1.0 * TEXHEIGHT / data->line_height;
	data->tex_pos = (data->draw_start - SCREENHEIGHT / 2
			+ data->line_height / 2) * data->step;
	while (data->draw_start < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		temp = things->map->world_map[data->map_y][data->map_x];
		if (temp >= DOOR0 && temp <= DOOR9)
			color = get_pixel(things->textures->door[temp - DOOR0],
					data->tex_x, data->tex_y);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(things->data, SCREENWIDTH - x,
				data->draw_start, color);
		data->draw_start++;
	}
}

void	render_sprites(t_things *things)
{
	int				i;
	int				x;
	t_walls_data	data;

	sort_doors(things->map, (int)things->pos_x, (int)things->pos_y);
	i = 0;
	while (i < things->map->n_doors)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			setup_walls_data(&data, things, x);
			raytrace(&data, things, i);
			if (data.hit == 2)
			{
				setup_info(&data, things);
				render_column(&data, things, x);
			}
			x++;
		}
		i++;
	}
}
