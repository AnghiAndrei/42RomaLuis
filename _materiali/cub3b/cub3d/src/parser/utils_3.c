#include "../../cub3d.h"

void	check_up_down(t_game *game, char **map)
{
	int x;

	x = 0;
	while (x < game->path.width - 1)
	{
		if (map[0][x] == ' ' || map[0][x] == '1')
			x++;
		else
			print_error("Error! wrong map!\n", game, 3);
	}
	x = 0;
	while (x < game->path.width - 1)
	{
		if (map[game->path.height - 1][x] == ' ' || map[game->path.height - 1][x] == '1')
			x++;
		else
			print_error("Error! wrong map!\n", game, 3);
	}
}