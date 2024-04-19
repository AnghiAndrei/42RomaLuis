#include "../../cub3d.h"

void check_args(t_game *game, int argc, const char **argv, int *fd)
{
	int map_counter;

	map_counter = 0;
    if (argc != 2 || check_exts((char *)argv[1]))
		print_error("Error! invalid or missing map!\n", game, 0);
	game->path.file_name = ft_strdup((char *)argv[1]);
	*fd = open(game->path.file_name, O_RDONLY);
    if (*fd == -1)
		print_error("Error! Wrong path!\n", game, 1);
	init_struct(game);
	if (!alloc_args(game, fd, &map_counter))
		print_error("missing map instructions!\n", game, 1);
	pop_map(game, fd, &map_counter);
	check_map(game, game->map);
}

int	alloc_args(t_game *game, int *fd, int *map_counter)
{
	char *line;

	line = get_next_line(*fd);
	(*map_counter)++;
	while (line)
	{
		if (line[0] == '\n')
		{
			line = next_line(&line, fd, map_counter);
			continue;
		}
		pop_args(line, game);
		if (full_check(game))
			break;
		free(line);
		line = get_next_line(*fd);
		(*map_counter)++;
	}
	check_params(game);
	free(line);
	return(1);
}

void	pop_args(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO", 2) && game->path.north == DEFAULT)
		game->path.north = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "EA", 2) && game->path.east == DEFAULT)
		game->path.east = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "SO", 2) && game->path.south == DEFAULT)
		game->path.south = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "WE", 2) && game->path.west == DEFAULT)
		game->path.west = ft_strtrim(line + 3, " \n");
	else if (!ft_strncmp(line, "C", 1) && game->path.cealing == DEFAULT)
		game->path.cealing = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "F", 1) && game->path.floor == DEFAULT)
		game->path.floor = ft_strtrim(line + 2, " \n");
	else
		print_error("Wrong map!\n", game, 1);
}

void pop_map(t_game *game, int *fd, int *map_counter)
{
	char 	*line;
	int 	i;

	i = 0;
	line = 0;
	line = skip_empty_lines(game, line, fd, map_counter);
	line = alloc_mtx(game, line, fd, map_counter);
	while (line)
	{
		game->map[i] = line;
		line = get_next_line(*fd);
		if (!line || line[0] == '\n')
			break;
		i++;
	}
	close(*fd);
	if (line && line[0] == '\n')
		invalid_map_error(game, line);
}

char *alloc_mtx(t_game *game, char *line, int *fd, int *map_counter)
{
	int z;

	z = 0;
	while (line)
	{
		if (line)
			free(line);
		line = get_next_line(*fd);
		game->path.height++;
	}
	close(*fd);
	game->map = malloc(sizeof(char *) * game->path.height);
	game->map[game->path.height - 1] = '\0';
	*fd = open (game->path.file_name, O_RDONLY);
	while (*map_counter > 0)
	{
		line = next_line(&line, fd, &z);
		(*map_counter)--;
	}
	return(line);
}