/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:56:35 by ebraho            #+#    #+#             */
/*   Updated: 2024/03/11 23:52:22 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_max_positions(t_map *map)
{
	int	y;
	int	old_max_x;
	int	temp;

	y = 0;
	old_max_x = 0;
	while (map->world_map[y] != NULL)
	{
		temp = ft_strlen(map->world_map[y]);
		if (temp > old_max_x)
			old_max_x = temp;
		y++;
	}
	map->max_x = old_max_x;
	map->max_y = y;
}

void	get_spawn_position(t_map *textures, int i, int j)
{
	if (textures->world_map[i][j] == NORD
		|| textures->world_map[i][j] == SOUTH
		|| textures->world_map[i][j] == WEST
		|| textures->world_map[i][j] == EAST)
	{
		textures->spawn_x = j;
		textures->spawn_y = i;
	}
}

int	parse_textures(char *line, t_map *textures)
{
	if (!ft_strncmp(line, "NO", 2) && textures->no == NULL)
		textures->no = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "SO", 2) && textures->so == NULL)
		textures->so = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "WE", 2) && textures->we == NULL)
		textures->we = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "EA", 2) && textures->ea == NULL)
		textures->ea = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "F", 1) && textures->str_floor == NULL)
		textures->str_floor = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "C", 1) && textures->str_ceilling == NULL)
		textures->str_ceilling = ft_strtrim(line + 2, " \n");
	else
		return (print_error("Wrong File. Wrong format information"));
	return (1);
}

int	parse_map(char **line, t_map *textures, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	next_line(line, fd);
	while (*line && (*line)[0] == '\n')
		next_line(line, fd);
	while (*line)
	{
		tmp = textures->str_map;
		textures->str_map = ft_strjoin(tmp, *line);
		free(tmp);
		next_line(line, fd);
	}
	textures->world_map = ft_split(textures->str_map, '\n');
	free(textures->str_map);
	if (!(*textures->world_map))
		return (print_error("Wrong File. Map is invalid"));
	i = -1;
	*line = ft_strtrim(textures->world_map[0], " ");
	while ((*line)[++i])
		if ((*line)[i] != WALL && (*line)[i] != SPACE)
			return (print_error("Wrong File. Map is invalid"));
	return (1);
}

void	load_doors(t_map *map)
{
	int	x;
	int	y;
	int	i;

	map->doors = malloc(sizeof(t_door) * map->n_doors);
	y = 0;
	i = 0;
	while (map->world_map[y] != NULL)
	{
		x = 0;
		while (map->world_map[y][x] != '\0')
		{
			if (map->world_map[y][x] == DOOR0)
			{
				map->doors[i].pos.x = x;
				map->doors[i].pos.y = y;
				map->doors[i].status = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}
