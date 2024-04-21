#include "cub3d.h"

int	click_x(t_game *game)
{
	mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	close_all(game, 3);
	return (0);
}

void	handle_movement(int keycode, t_game *game)
{
	if (keycode == XK_w)
	{
		game->moves.w = 1;
		game->moves.move_speed = .05;
	}
	if (keycode == XK_a)
	{
		game->moves.a = 1;
		game->moves.move_side_speed = .05;
	}
	if (keycode == XK_s)
	{
		game->moves.s = 1;
		game->moves.move_speed = -.05;
	}
	if (keycode == XK_d)
	{
		game->moves.d = 1;
		game->moves.move_side_speed = -.05;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 53)
		close_all(game, 3);
	handle_movement(keycode, game);
	if (keycode == XK_Left)
	{
		game->moves.l = 1;
		game->moves.rot_speed = -.05;
	}
	if (keycode == XK_Right)
	{
		game->moves.r = 1;
		game->moves.rot_speed = .05;
	}
	return (1);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w || keycode == XK_s)
		game->moves.move_speed = 0;
	if (keycode == XK_d || keycode == XK_a)
		game->moves.move_side_speed = 0;
	if (keycode == XK_w)
		game->moves.w = 0;
	if (keycode == XK_s)
		game->moves.s = 0;
	if (keycode == XK_d)
		game->moves.d = 0;
	if (keycode == XK_a)
		game->moves.a = 0;
	if (keycode == 113 || keycode == 114)
		game->moves.rot_speed = 0;
	if (keycode == XK_Left)
		game->moves.l = 0;
	if (keycode == XK_Right)
		game->moves.r = 0;
	return (1);
}