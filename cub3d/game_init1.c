/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:48:20 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/17 18:53:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_background(t_master *m, int y, int x)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*pos;
	char	*address;

	m->backgroud = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	address = mlx_get_data_addr(m->backgroud, &bits_per_pixel, &size_line,
			&endian);
	while (y != HEIGHT)
	{
		x = 0;
		while (x != WIDTH)
		{
			pos = address + (y * size_line + x * (bits_per_pixel / 8));
			if (y > HEIGHT / 2)
				*(unsigned int *)pos = m->colc;
			else
				*(unsigned int *)pos = m->colf;
			x++;
		}
		y++;
	}
}
