/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:10:22 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/22 00:21:34 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	render_column(t_walls_data *data, t_things *things, int x)
{
	int				y;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
		{
			if (data->side != 0 && data->step_y == -1)
				my_mlx_pixel_put(things->data, SCREENWIDTH - x, y,
					get_pixel(things->textures->no, data->tex_x, data->tex_y));
			else if (data->side != 0 && data->step_y == 1)
				my_mlx_pixel_put(things->data, SCREENWIDTH - x, y,
					get_pixel(things->textures->so, data->tex_x, data->tex_y));
			else if (data->step_x == -1)
				my_mlx_pixel_put(things->data, SCREENWIDTH - x, y,
					get_pixel(things->textures->we, data->tex_x, data->tex_y));
			else if (data->step_x == 1)
				my_mlx_pixel_put(things->data, SCREENWIDTH - x, y,
					get_pixel(things->textures->ea, data->tex_x, data->tex_y));
		}
		y++;
	}
}

static void	raytrace(t_walls_data *data, t_things *things)
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
		data->hit = things->map->world_map[data->map_y][data->map_x] == WALL;
	}
	data->w_dist = f_t(data->side == 0, data->side_dist_x - data->delta_x,
			data->side_dist_y - data->delta_y);
	data->line_height = (int)(SCREENHEIGHT / data->w_dist);
	data->draw_start = -data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_end >= SCREENHEIGHT)
		data->draw_end = SCREENHEIGHT - 1;
}

void	setup_walls_data(t_walls_data *data, t_things *things, int x)
{
	data->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	data->ray_dir_x = things->dir_x + things->plane_x * data->camera_x;
	data->ray_dir_y = things->dir_y + things->plane_y * data->camera_x;
	data->map_x = (int)things->pos_x;
	data->map_y = (int)things->pos_y;
	data->hit = 0;
	data->delta_x = f_t(data->ray_dir_x == 0, 1e30, fabs(1 / data->ray_dir_x));
	data->delta_y = f_t(data->ray_dir_y == 0, 1e30, fabs(1 / data->ray_dir_y));
	data->step_x = f_t(data->ray_dir_x < 0, -1, 1);
	data->side_dist_x = f_t(data->ray_dir_x < 0, (things->pos_x - data->map_x)
			* data->delta_x, (data->map_x + 1.0 - things->pos_x)
			* data->delta_x);
	data->step_y = f_t(data->ray_dir_y < 0, -1, 1);
	data->side_dist_y = f_t(data->ray_dir_y < 0, (things->pos_y - data->map_y)
			* data->delta_y, (data->map_y + 1.0 - things->pos_y)
			* data->delta_y);
}

void	render_walls(t_things *things)
{
	int				x;
	t_walls_data	data;

	x = 0;
	while (x < SCREENWIDTH)
	{
		setup_walls_data(&data, things, x);
		raytrace(&data, things);
		data.wall_x = f_t(data.side == 0, things->pos_y + data.w_dist
				* data.ray_dir_y, things->pos_x + data.w_dist * data.ray_dir_x);
		data.wall_x -= floor((data.wall_x));
		data.tex_x = (int)(data.wall_x * (double)TEXWIDTH);
		if (data.side == 0 && data.ray_dir_x > 0)
			data.tex_x = TEXWIDTH - data.tex_x - 1;
		if (data.side == 1 && data.ray_dir_y < 0)
			data.tex_x = TEXWIDTH - data.tex_x - 1;
		data.step = 1.0 * TEXHEIGHT / data.line_height;
		data.tex_pos = (data.draw_start - SCREENHEIGHT / 2
				+ data.line_height / 2) * data.step;
		render_column(&data, things, x);
		x++;
	}
}
