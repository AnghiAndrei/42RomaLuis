#include "../../cub3d.h"

void	set_data(t_walls *data, t_mlx *mlx, int x)
{
	data->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	data->ray_dir_x = mlx->dir_x + mlx->plane_x * data->camera_x;
	data->ray_dir_y = mlx->dir_y + mlx->plane_y * data->camera_x;
	data->map_x = (int)mlx->pos_x;
	data->map_y = (int)mlx->pos_y;
	data->hit = 0;
	data->delta_x = ft_double(data->ray_dir_x == 0, 1e30, fabs(1 / data->ray_dir_x));
	data->delta_y = ft_double(data->ray_dir_y == 0, 1e30, fabs(1 / data->ray_dir_y));
	data->step_x = ft_double(data->ray_dir_x < 0, -1, 1);
	data->side_dist_x = ft_double(data->ray_dir_x < 0, (mlx->pos_x - data->map_x)
			* data->delta_x, (data->map_x + 1.0 - mlx->pos_x)
			* data->delta_x);
	data->step_y = ft_double(data->ray_dir_y < 0, -1, 1);
	data->side_dist_y = ft_double(data->ray_dir_y < 0, (mlx->pos_y - data->map_y)
			* data->delta_y, (data->map_y + 1.0 - mlx->pos_y)
			* data->delta_y);
}

void	check_distance(t_walls *data, char **map)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		data->hit = map[data->map_y][data->map_x] == '1';
	}
	data->w_dist = ft_double(data->side == 0, data->side_dist_x - data->delta_x,
			data->side_dist_y - data->delta_y);
	data->line_height = (int)(SCREENHEIGHT / data->w_dist);
	data->draw_start = -data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_end >= SCREENHEIGHT)
		data->draw_end = SCREENHEIGHT - 1;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}