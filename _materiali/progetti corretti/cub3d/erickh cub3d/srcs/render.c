/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:26:35 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/23 17:25:08 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_skybox(t_things *things)
{
	int	y;
	int	x;

	y = SCREENHEIGHT / 2 + 1;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			my_mlx_pixel_put(things->data, SCREENWIDTH - x,
				y, things->map->floor.hex);
			my_mlx_pixel_put(things->data, SCREENWIDTH - x,
				SCREENHEIGHT - y - 1, things->map->ceilling.hex);
			++x;
		}
		y++;
	}
}

double	f_t(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

void	render_everything(t_things *things)
{
	render_skybox(things);
	render_walls(things);
	render_sprites(things);
	update_minimap(things);
	mlx_put_image_to_window(things->mlx, things->window,
		things->data->img, 0, 0);
}

void	destroy_textures(t_things *things)
{
	int	i;

	mlx_destroy_image(things->mlx, things->textures->no->img);
	free(things->textures->no);
	mlx_destroy_image(things->mlx, things->textures->so->img);
	free(things->textures->so);
	mlx_destroy_image(things->mlx, things->textures->we->img);
	free(things->textures->we);
	mlx_destroy_image(things->mlx, things->textures->ea->img);
	free(things->textures->ea);
	i = 0;
	while (i < things->map->n_doors)
	{
		mlx_destroy_image(things->mlx, things->textures->door[i]->img);
		free(things->textures->door[i++]);
	}
}

int	click_cross(int keycode, t_things *things)
{
	int	i;

	destroy_textures(things);
	mlx_destroy_window(things->mlx, things->window);
	free(things->textures);
	free(things->data);
	free(things->mlx);
	free(things);
	exit(0);
}
