#include "../../cub3d.h"

void	init_game(t_game *game)
{
	set_vars(game);
	load_imgs(game);
	render_things(game);
	mlx_hook(game->mlx.window, 17, 0, &click_x, game);
	mlx_loop_hook(game->mlx.mlx, &game_loop, game);
	mlx_hook(game->mlx.window, 3, 1L<<1, &handle_keyrelease, game);
	mlx_hook(game->mlx.window, 2, 1L<<0, &handle_keypress, game);
	mlx_loop(game->mlx.mlx);
}

void	set_vars(t_game *game)
{
	game->mlx.pos_x = game->spawn.x + 0.5;
	game->mlx.pos_y = game->spawn.y + 0.5;
	game->mlx.dir_x = 0;
	game->mlx.dir_y = 0;
	game->mlx.plane_x = 0;
	game->mlx.plane_y = 0;
	set_pos(game);
	game->moves.rot_speed = 0;
	game->moves.move_speed = 0;
	game->mlx.mlx = mlx_init();
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, SCREENWIDTH, SCREENHEIGHT);
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img, 
			&game->mlx.img.bits_per_pixel, &game->mlx.img.line_length, 
			&game->mlx.img.endian);
	game->mlx.window = mlx_new_window(game->mlx.mlx, SCREENWIDTH, SCREENHEIGHT, "CUB'TRE'D");
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img,
			 0, 0);
}

void	load_imgs(t_game *game)
{
	int	z;
	int	r;

	r = 64;
	z = 64;
	game->mlx.ea.img = mlx_xpm_file_to_image(game->mlx.mlx, game->path.east, 
			&r, &z);
	if (!game->mlx.ea.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.so.img = mlx_xpm_file_to_image(game->mlx.mlx, game->path.south, 
			&r, &z);
	if (!game->mlx.so.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.we.img = mlx_xpm_file_to_image(game->mlx.mlx, game->path.west, 
			&r, &z);
if (!game->mlx.we.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.no.img = mlx_xpm_file_to_image(game->mlx.mlx, game->path.north, 
			&r, &z);
	if (!game->mlx.no.img)
		print_error("ERROR. Invalid textures.", game, 0);
	get_addresses(game);
}

void	set_pos(t_game *game)
{
	if (game->spawn.direction == 'W')
	{
		game->mlx.dir_x = -1;
		game->mlx.plane_y = 0.66;
	}
	if (game->spawn.direction == 'E')
	{
		game->mlx.dir_x = 1;
		game->mlx.plane_y = -0.66;
	}
	if (game->spawn.direction == 'N')
	{
		game->mlx.dir_y = -1;
		game->mlx.plane_x = -0.66;
	}
	if (game->spawn.direction == 'S')
	{
		game->mlx.dir_y = 1;
		game->mlx.plane_x = 0.66;
	}
}

void	get_addresses(t_game *game)
{
	game->mlx.ea.addr = mlx_get_data_addr(game->mlx.ea.img, 
			&game->mlx.ea.bits_per_pixel, &game->mlx.ea.line_length, 
			&game->mlx.ea.endian);
	game->mlx.so.addr = mlx_get_data_addr(game->mlx.so.img, 
			&game->mlx.so.bits_per_pixel, &game->mlx.so.line_length, 
			&game->mlx.so.endian);
	game->mlx.we.addr = mlx_get_data_addr(game->mlx.we.img, 
			&game->mlx.we.bits_per_pixel, &game->mlx.we.line_length, 
			&game->mlx.we.endian);
	game->mlx.no.addr = mlx_get_data_addr(game->mlx.no.img, 
			&game->mlx.no.bits_per_pixel, &game->mlx.no.line_length, 
			&game->mlx.no.endian);
}
