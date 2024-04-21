/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 21:19:08 by everolla          #+#    #+#             */
/*   Updated: 2024/04/05 21:20:18 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_exts(char *map)
{
	if (map[ft_strlen(map) - 1] == 'b' && map[ft_strlen(map) - 2] == 'u'
		&& map[ft_strlen(map) - 3] == 'c' && map[ft_strlen(map) - 4] == '.')
		return (0);
	return (1);
}

void	init_struct(t_game *game)
{
	game->path.north = DEFAULT;
	game->path.west = DEFAULT;
	game->path.east = DEFAULT;
	game->path.south = DEFAULT;
	game->path.cealing = DEFAULT;
	game->path.floor = DEFAULT;
	game->path.width = DEFAULT;
	game->path.height = DEFAULT;
}

int	full_check(t_game *game)
{
	if (game->path.north != DEFAULT)
		if (game->path.west != DEFAULT)
			if (game->path.east != DEFAULT)
				if (game->path.south != DEFAULT)
					if (game->path.cealing != DEFAULT)
						if (game->path.floor != DEFAULT)
							return (1);
	return (0);
}

void	check_params(t_game *game)
{
	if (!full_check(game))
		print_error("Error! wrong map!\n", game, 1);
	check_colors(game, game->path.cealing, &game->ceiling_color);
	check_colors(game, game->path.floor, &game->floor_color);
}

int	check_colors(t_game *game, char *color, t_rgb *colors)
{
	char **rgb;
	int i;

	i = 0;
	rgb = ft_split(color, ',');
	while (rgb[i])
		i++;
	if (i != 3)
		print_error("Error! Wrong Colors!\n", game, 0);
	colors->r = ft_atoi(rgb[0]);
	colors->g = ft_atoi(rgb[1]);
	colors->b = ft_atoi(rgb[2]);
	if (colors->r < 0 || colors->r > 255 || colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
		print_error("Error! Wrong Colors!\n", game, 0);
	colors->hex = colors->r;
	colors->hex = (colors->hex << 8) + colors->g;
	colors->hex = (colors->hex << 8) + colors->b;
	free_rgb(rgb);
	return (1);
}