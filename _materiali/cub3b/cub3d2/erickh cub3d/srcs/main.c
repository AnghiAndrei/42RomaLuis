/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:19:11 by ebraho            #+#    #+#             */
/*   Updated: 2024/03/22 18:19:23 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mlx.h"

#include "../includes/cub3d.h"

static void	init_textures(t_map *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->str_floor = NULL;
	textures->str_ceilling = NULL;
	textures->str_map = malloc(1);
	textures->str_map[0] = '\0';
	textures->n_doors = 0;
	textures->spawn_x = -1;
	textures->spawn_y = -1;
}

static int	read_file(char **line, t_map *textures, int fd)
{
	*line = get_next_line(fd);
	while (*line)
	{
		if (!ft_strncmp(*line, "\n", 1))
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		if (!parse_textures(*line, textures))
			return (0);
		if (textures->no && textures->so && textures->we && textures->ea
			&& textures->str_floor && textures->str_ceilling)
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
	check_textures(textures);
	if (!parse_map(line, textures, fd))
		return (0);
	return (1);
}

static void	parse_doors_run(t_map *textures, int fd)
{
	load_doors(textures);
	close(fd);
	init_raycasting(textures);
}

int	first_map_check(char *line)
{
	if ((line[0] != WALL && line[0] != SPACE)
		|| (line[ft_strlen(line) - 1] != WALL
			&& line[ft_strlen(line) - 1] != SPACE))
		return (print_error("Wrong File. Map is invalid"));
	free(line);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map		textures;
	char		*line;
	int			i;
	int			j;

	i = 0;
	if (!check_params(argc, argv, &fd))
		return (0);
	init_textures(&textures);
	if (!read_file(&line, &textures, fd))
		return (0);
	i = 0;
	while (line)
	{
		if (!first_map_check(line))
			return (0);
		line = ft_strtrim(textures.world_map[++i], " ");
	}
	free(line);
	line = ft_strtrim(textures.world_map[--i], " ");
	if (check_map(line, &textures))
		parse_doors_run(&textures, fd);
	return (0);
}
