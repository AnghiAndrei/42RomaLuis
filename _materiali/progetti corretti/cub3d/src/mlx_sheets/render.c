#include "../../cub3d.h"

void	render_things(t_game *game)
{
	render_floor_ceiling(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img, 0, 0);
}

void	render_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		set_data(&game->walls_data, &game->mlx, x);
		check_distance(&game->walls_data, game->map);
		game->walls_data.wall_x = ft_double(game->walls_data.side == 0, game->mlx.pos_y + game->walls_data.w_dist
				* game->walls_data.ray_dir_y, game->mlx.pos_x + game->walls_data.w_dist * game->walls_data.ray_dir_x);
		game->walls_data.wall_x -= floor((game->walls_data.wall_x));
		game->walls_data.tex_x = (int)(game->walls_data.wall_x * (double)TEXWIDTH);
		if (game->walls_data.side == 0 && game->walls_data.ray_dir_x > 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		if (game->walls_data.side == 1 && game->walls_data.ray_dir_y < 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		game->walls_data.step = 1.0 * TEXHEIGHT / game->walls_data.line_height;
		game->walls_data.tex_pos = (game->walls_data.draw_start - SCREENHEIGHT / 2
				+ game->walls_data.line_height / 2) * game->walls_data.step;
		render_y(&game->walls_data, &game->mlx, x);
		x++;
	}
}

void	render_floor_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = SCREENHEIGHT / 2 + 1;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			my_mlx_pixel_put(&game->mlx.img, SCREENWIDTH - x,
				y, game->floor_color.hex);
			my_mlx_pixel_put(&game->mlx.img, SCREENWIDTH - x,
				SCREENHEIGHT - y - 1, game->ceiling_color.hex);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_y(t_walls *data, t_mlx *mlx, int x)
{
	int				y;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
		{
			if (data->side != 0 && data->step_y == -1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->no, data->tex_x, data->tex_y));
			else if (data->side != 0 && data->step_y == 1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->so, data->tex_x, data->tex_y));
			else if (data->step_x == -1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->we, data->tex_x, data->tex_y));
			else if (data->step_x == 1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->ea, data->tex_x, data->tex_y));
		}
		y++;
	}
}