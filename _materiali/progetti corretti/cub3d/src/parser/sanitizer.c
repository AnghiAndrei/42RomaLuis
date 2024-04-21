#include "../../cub3d.h"

void check_map(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = 0;
	realloc_map(game);
	check_left_right(game, game->map);
	check_up_down(game, game->map);
	while (i < game->path.height - 1)
	{
		while (x < game->path.width - 1)
		{
			if(map[i][x] == ' ')
				check_borders(game, game->map, i, x);
			else	
				take_spawn(game, map[i][x], i, x);
			x++;
		}
		x = 0;
		i++;
	}
}

void realloc_map(t_game *game)
{
	int i;
	int r;

	i = 0;
	while (i < game->path.height)
	{
		r = ft_strlen(game->map[i]);
		if (r > game->path.width)
			game->path.width = r;
		i++;
	}
	i = 0;
	while (i < game->path.height)
	{
		game->map[i] = realloc_line(game->map[i], game->path.width);
		i++;
	}
}

char *realloc_line(char *line, int r)
{
	char *new_line;
	int i;

	i = 0;
	new_line = malloc(r * sizeof(char));
	new_line[r - 1] = '\0';
	while(line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	while (i < r)
		new_line[i++] = ' ';
	return (new_line);
}

void take_spawn(t_game *game, char c, int y, int x)
{
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
	{
		game->spawn.direction = c;
		game->spawn.x = x;
		game->spawn.y = y;
	}
	else if (c == '1' || c == '0')
		return;
	else
		print_error("Error! invalid map input!\n", game, 3);
}

void	check_borders(t_game *game, char **map, int i, int x)
{
	if ((i - 1) >= 0)
		if ((map[i - 1][x] != ' ' && map[i - 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((x - 1) >= 0)
		if ((map[i][x - 1] != ' ' && map[i][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((i + 1) < game->path.height)
		if ((map[i + 1][x] != ' ' && map[i + 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((x + 1) < game->path.width)
		if ((map[i][x + 1] != ' ' && map[i][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((i + 1) < game->path.height && (x + 1) < game->path.width)
		if ((map[i + 1][x + 1] != ' ' && map[i + 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((i + 1) < game->path.height && (x - 1) >= 0)
		if ((map[i + 1][x - 1] != ' ' && map[i + 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((i - 1) >= 0 && (x + 1) < game->path.width)
		if ((map[i - 1][x + 1] != ' ' && map[i - 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
	if ((i - 1) >= 0 && (x - 1) >= 0)
		if ((map[i - 1][x - 1] != ' ' && map[i - 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 3);
}