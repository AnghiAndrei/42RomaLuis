/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:48:20 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 16:56:53 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img(t_img *i, char *path, t_master *m)
{
	i->img = mlx_xpm_file_to_image(m->mlx, path, &i->line_l, &i->endian);
	i->addr = mlx_get_data_addr(i->img, &i->bxp, &i->line_l, &i->endian);
}

void	game_init5(t_master *m)
{
	if (m->map[(int)m->yp][(int)m->xp] == 'W')
	{
		m->dir_x = -1;
		m->plane_y = 0.66;
	}
	if (m->map[(int)m->yp][(int)m->xp] == 'E')
	{
		m->dir_x = 1;
		m->plane_y = -0.66;
	}
	if (m->map[(int)m->yp][(int)m->xp] == 'N')
	{
		m->dir_x = -1;
		m->plane_y = -0.66;
	}
	if (m->map[(int)m->yp][(int)m->xp] == 'S')
	{
		m->dir_x = 1;
		m->plane_y = 0.66;
	}
}
