/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_utilitis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:40:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/06/07 13:13:57 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_background(t_master *m, int y, int x)
{
	char	*pos;

	while (y < HEIGHT / 2 + 1)
	{
		x = 0;
		while (x < WIDTH)
		{
			pos = m->bg.addr + (y * m->bg.line_l + x * (m->bg.bxp / 8));
			*(unsigned int *)pos = m->colc;
			pos = m->bg.addr + ((y + (HEIGHT / 2) + 1) * m->bg.line_l + x
					* (m->bg.bxp / 8));
			*(unsigned int *)pos = m->colf;
			x++;
		}
		y++;
	}
}

float	ternals(int b, float t, float f)
{
	if (b)
		return (t);
	return (f);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_l + x * (data->bxp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_master *m, t_img *img, int x, int y)
{
	char	*dest;

	y++;
	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_l + x * (img->bxp / 8));
	if (ft_strncmp(dest, "", 1) == 0)
	{
		dest = m->bg.addr + (1 * m->bg.line_l + 1 * (m->bg.bxp / 8));
		return (*(unsigned int *)dest);
	}
	return (*(unsigned int *)dest);
}
