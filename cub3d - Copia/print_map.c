/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 16:59:01 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_var(t_master *m, int x)
{
	m->camera_x = 2 * x / (double)WIDTH - 1;
	m->ray_dir_x = m->dir_x + m->plane_x * m->camera_x;
	m->ray_dir_y = m->dir_y + m->plane_y * m->camera_x;
	m->map_x = (int)m->pos_x;
	m->map_y = (int)m->pos_y;
	m->hit = 0;
	m->delta_x = ternals(m->ray_dir_x == 0, 1e30, fabs(1 / m->ray_dir_x));
	m->delta_y = ternals(m->ray_dir_y == 0, 1e30, fabs(1 / m->ray_dir_y));
	m->step_x = ternals(m->ray_dir_x < 0, -1, 1);
	m->side_dist_x = ternals(m->ray_dir_x < 0, (m->pos_x - m->map_x)
			* m->delta_x, (m->map_x + 1.0 - m->pos_x) * m->delta_x);
	m->step_y = ternals(m->ray_dir_y < 0, -1, 1);
	m->side_dist_y = ternals(m->ray_dir_y < 0, (m->pos_y - m->map_y)
			* m->delta_y, (m->map_y + 1.0 - m->pos_y) * m->delta_y);
}

void	check_distance(t_master *m, char **map)
{
	while (m->hit == 0)
	{
		if (m->side_dist_x < m->side_dist_y)
		{
			m->side_dist_x += m->delta_x;
			m->map_x += m->step_x;
			m->side = 0;
		}
		else
		{
			m->side_dist_y += m->delta_y;
			m->map_y += m->step_y;
			m->side = 1;
		}
		m->hit = map[m->map_y][m->map_x] == '1';
	}
	m->w_dist = ternals(m->side == 0, m->side_dist_x - m->delta_x,
			m->side_dist_y - m->delta_y);
	m->line_height = (int)(HEIGHT / m->w_dist);
	m->draw_start = -m->line_height / 2 + HEIGHT / 2;
	if (m->draw_start < 0)
		m->draw_start = 0;
	m->draw_end = m->line_height / 2 + HEIGHT / 2;
	if (m->draw_end >= HEIGHT)
		m->draw_end = HEIGHT - 1;
}

void	render_y(t_master *m, int x, int y)
{
	y = m->draw_start;
	while (y < m->draw_end)
	{
		m->tex_y = (int)m->tex_pos & (TEXHEIGHT - 1);
		m->tex_pos += m->step;
		if (m->hit == 1)
		{
			if (m->side != 0 && m->step_y == -1 && m->a == 0 && m->a++)
				my_mlx_pixel_put(&m->bg, WIDTH - x, y,
					get_pixel(m, &m->no, m->tex_x, m->tex_y));
			else if (m->side != 0 && m->step_y == -1 && m->a == 1 && m->a--)
				my_mlx_pixel_put(&m->bg, WIDTH - x, y,
					get_pixel(m, &m->no2, m->tex_x, m->tex_y));
			else if (m->side != 0 && m->step_y == 1)
				my_mlx_pixel_put(&m->bg, WIDTH - x, y,
					get_pixel(m, &m->so, m->tex_x, m->tex_y));
			else if (m->step_x == -1)
				my_mlx_pixel_put(&m->bg, WIDTH - x, y,
					get_pixel(m, &m->we, m->tex_x, m->tex_y));
			else if (m->step_x == 1)
				my_mlx_pixel_put(&m->bg, WIDTH - x, y,
					get_pixel(m, &m->ea, m->tex_x, m->tex_y));
		}
		y++;
	}
}

void	print_map(t_master *m, int x)
{
	mlx_destroy_image(m->mlx, m->bg.img);
	m->bg.img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->bg.addr = mlx_get_data_addr(m->bg.img, &m->bg.bxp,
			&m->bg.line_l, &m->bg.endian);
	set_background(m, 0, 0);
	while (x < WIDTH)
	{
		set_var(m, x);
		check_distance(m, m->map);
		m->wall_x = ternals(m->side == 0, m->pos_y + m->w_dist
				* m->ray_dir_y, m->pos_x + m->w_dist * m->ray_dir_x);
		m->wall_x -= floor((m->wall_x));
		m->tex_x = (int)(m->wall_x * (double)TEXWIDTH);
		if (m->side == 0 && m->ray_dir_x > 0)
			m->tex_x = TEXWIDTH - m->tex_x - 1;
		if (m->side == 1 && m->ray_dir_y < 0)
			m->tex_x = TEXWIDTH - m->tex_x - 1;
		m->step = 1.0 * TEXHEIGHT / m->line_height;
		m->tex_pos = (m->draw_start - HEIGHT / 2 + m->line_height / 2)
			* m->step;
		render_y(m, x, 0);
		x++;
	}
	mlx_clear_window(m->mlx, m->win);
	mlx_put_image_to_window(m->mlx, m->win, m->bg.img, 0, 0);
}
