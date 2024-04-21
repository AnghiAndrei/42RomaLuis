/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:39:00 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/23 00:59:40 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_distance(int x1, int y1, int x2, int y2)
{
	return (pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int	print_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(0);
	return (0);
}

int	str_to_color(char *str, t_color *color)
{
	char	**colors;
	int		i;
	int		c;

	i = 0;
	colors = ft_split(str, ',');
	while (colors[i])
		++i;
	if (i != 3)
		return (0);
	color->r = ft_atoi(colors[0]);
	color->g = ft_atoi(colors[1]);
	color->b = ft_atoi(colors[2]);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (0);
	color->hex = color->r;
	color->hex = (color->hex << 8) + color->g;
	color->hex = (color->hex << 8) + color->b;
	free_colors(colors, str);
	return (1);
}

long	get_timestamp(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000);
}

void	sort_doors(t_map *textures, int x, int y)
{
	int		i;
	int		j;
	t_door	temp;

	i = 1;
	while (i < textures->n_doors)
	{
		j = i - 1;
		while (j >= 0)
		{
			if (get_distance(x, y,
					textures->doors[j].pos.x, textures->doors[j].pos.y)
				< get_distance(x, y,
					textures->doors[i].pos.x, textures->doors[i].pos.y))
			{
				temp = textures->doors[i];
				textures->doors[i] = textures->doors[j];
				textures->doors[j] = temp;
			}
			j--;
		}
		i++;
	}
}
