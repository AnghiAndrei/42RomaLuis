/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/18 17:02:50 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

static void	set_var(t_master *m, int x)
{
	m->camera_x = 2 * x / (double)WIDTH - 1;
	m->ray_dir_x = m->dir_x + m->plane_x * m->camera_x;
	m->ray_dir_y = m->dir_y + m->plane_y * m->camera_x;
	m->map_x = (int)m->xp;
	m->map_y = (int)m->yp;
	m->hit = 0;
	m->delta_x = ft_double(m->ray_dir_x == 0, 1e30, fabs(1 / m->ray_dir_x));
	m->delta_y = ft_double(m->ray_dir_y == 0, 1e30, fabs(1 / m->ray_dir_y));
	m->step_x = ft_double(m->ray_dir_x < 0, -1, 1);
	m->side_dist_x = ft_double(m->ray_dir_x < 0, (m->pos_x - m->map_x)
			* m->delta_x, (m->map_x + 1.0 - m->pos_x) * m->delta_x);
	m->step_y = ft_double(m->ray_dir_y < 0, -1, 1);
	m->side_dist_y = ft_double(m->ray_dir_y < 0, (m->pos_y - m->map_y)
			* m->delta_y, (m->map_y + 1.0 - m->pos_y) * m->delta_y);
}

void	print_map(t_master *m, int x)
{
	while (x < WIDTH)
	{
		set_var(m, x);
		x++;
	}
	mlx_clear_window(m->mlx, m->win);
	mlx_put_image_to_window(m->mlx, m->win, m->backgroud, 0, 0);
}
