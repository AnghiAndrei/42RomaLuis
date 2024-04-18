/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:48:20 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/18 17:02:01 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_background(t_master *m, int y, int x)
{
	char	*pos;

	m->backgroud = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->address = mlx_get_data_addr(m->backgroud, &m->bits_per_pixel,
			&m->size_line, &m->endianimg);
	while (y != HEIGHT)
	{
		x = 0;
		while (x != WIDTH)
		{
			pos = m->address + (y * m->size_line + x * (m->bits_per_pixel / 8));
			if (y > HEIGHT / 2)
				*(unsigned int *)pos = m->colc;
			else
				*(unsigned int *)pos = m->colf;
			x++;
		}
		y++;
	}
}

void	game_init5(t_master *m)
{
	m->pos_x = m->xp + 0.5;
	m->pos_y = m->yp + 0.5;
	m->plane_x = 0;
	m->plane_y = 0;
	m->dir_x = 0;
	m->dir_y = 0;
	m->wall = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->address2 = mlx_get_data_addr(m->wall, &m->bits_per_pixel2,
			&m->size_line2, &m->endianimg2);
}
