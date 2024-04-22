/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/22 17:13:24 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_minimap(char **map, t_master *m)
{
	int		x;
	int		y;

	if (m->minimapp == 0)
		return ;
	y = -1;
	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(m->mlx, m->win, m->mwall,
					x * MG, y * MG);
			if (map[y][x] == '0')
				mlx_put_image_to_window(m->mlx, m->win, m->mfloor,
					x * MG, y * MG);
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->mplayer, m->xp * MG, m->yp * MG);
}
