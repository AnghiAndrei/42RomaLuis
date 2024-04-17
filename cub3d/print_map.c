/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/17 14:05:29 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_master *m)
{
	int		y;
	int		x;

	printf("hola\n");
	mlx_clear_window(m->mlx, m->win);
	x = 0;
	while (WIDTH != x)
	{
		y = 0;
		while (HEIGHT != y)
		{
			if (y / 2 > HEIGHT / 2)
				mlx_put_image_to_window(m->mlx, m->win, m->mfloor,
					x * MG, y * MG);
			else
				mlx_put_image_to_window(m->mlx, m->win, m->mfloor,
					x * MG, y * MG);
			y++;
		}
		x++;
	}
	
}
