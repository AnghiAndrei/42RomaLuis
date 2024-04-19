/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:46:54 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/23 00:27:02 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_data	*load_image(t_things *things, char *path)
{
	t_data	*data;
	int		a;
	int		b;

	data = malloc(sizeof(t_data));
	a = 64;
	b = 64;
	data->img = mlx_png_file_to_image(things->mlx, path, &a, &b);
	if (data->img == NULL)
	{
		free(data);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data);
}

static int	load_door_textures(t_things *things)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	tmp = malloc(ft_strlen(DOOR_PATH));
	tmp[0] = '\0';
	path = ft_strjoin(tmp, DOOR_PATH);
	while (i < 10)
	{
		things->textures->door[i] = load_image(things, path);
		if (things->textures->door[i] == NULL)
			return (print_error("Invalid textures."));
		path[12]++;
		i++;
	}
	free(tmp);
	free(path);
	return (1);
}

unsigned int	get_pixel(t_data *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	load_textures(t_things *things)
{
	int		i;
	char	*path;

	things->textures = malloc(sizeof(t_textures));
	things->textures->ea = load_image(things, things->map->ea);
	if (things->textures->ea == NULL)
		return (print_error("Invalid textures."));
	things->textures->no = load_image(things, things->map->no);
	if (things->textures->no == NULL)
		return (print_error("Invalid textures."));
	things->textures->so = load_image(things, things->map->so);
	if (things->textures->so == NULL)
		return (print_error("Invalid textures."));
	things->textures->we = load_image(things, things->map->we);
	if (things->textures->we == NULL)
		return (print_error("Invalid textures."));
	return (load_door_textures(things));
}
