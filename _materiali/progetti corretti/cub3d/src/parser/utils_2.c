#include "../../cub3d.h"

char	*skip_empty_lines(t_game *game, char *line, int *fd, int *map_counter)
{
	line = get_next_line(*fd);
	(*map_counter)++;
	while (line && line[0] == '\n')
		line = next_line(&line, fd, map_counter);
	if (line[0] == '\0')
		print_error("Error! Wrong map!\n", game, 1);
	return (line);
}

char *next_line(char **line, int *fd, int *map_counter)
{
	char *l;
	free(*line);
	l = get_next_line(*fd);
	(*map_counter)++;
	return (l);
}

void	invalid_map_error(t_game *game, char *line)
{
	free (line);
	print_error("Error! Invalid Map!\n", game, 1);	
}

void	check_left_right(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (i < game->path.height - 1)
	{
		while (x < game->path.width - 1)
		{
			if (map[i][x] == ' ' && ++x)
				continue;
			if (map[i][x] == '1')
				break;
			else
				print_error("Error! wrong map!\n", game, 3);
		}
		x = 0;
		i++;
	}
	check_right(game, map);
}

void	check_right(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = game->path.width;
	while (i < game->path.height - 1)
	{
		while (x < game->path.width - 1)
		{
			if (map[i][x] == ' ' && --x)
				continue;
			if (map[i][x] == '1')
				break;
			else
				print_error("Error! wrong map!\n", game, 3);
		}
		x = game->path.width;
		i++;
	}
}
