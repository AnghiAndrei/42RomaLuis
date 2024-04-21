#include "cub3d.h"

void cls(t_game *game)
{
	free(game);
	exit(0);
}
void	close_all(t_game *game, int r)
{
	int i;

	if (r == 0)
		cls(game);
	free(game->path.east);
	free(game->path.north);
	free(game->path.west);
	free(game->path.south);
	free(game->path.cealing);
	free(game->path.floor);
	free(game->path.file_name);
	if (r != 3)
		cls(game);
	i = 0;
	while (i < game->path.height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	cls(game);
}

int check_exts(char *map)
{
	if (map[ft_strlen(map) - 1] == 'b' && map[ft_strlen(map) - 2] == 'u' 
		&& map[ft_strlen(map) - 3] == 'c' && map[ft_strlen(map)-4] == '.')
        return (0);
    return (1);
}

void	init_struct(t_game *game)
{
	game->path.north = DEFAULT;
	game->path.west = DEFAULT;
	game->path.east = DEFAULT;
	game->path.south = DEFAULT;
	game->path.cealing = DEFAULT;
	game->path.floor = DEFAULT;
	game->path.width = DEFAULT;
	game->path.height = DEFAULT;
}

int	print_error(char *str, t_game *game, int i)
{
	printf("%s", str);
	close_all(game, i);
	return(0);
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
		print_error("Wrong map!\n", game, 0);
}

int	full_check(t_game *game)
{
	if (game->path.north != DEFAULT)
		if (game->path.west != DEFAULT)
			if (game->path.east != DEFAULT)
				if (game->path.south != DEFAULT)
					if (game->path.cealing != DEFAULT)
						if (game->path.floor != DEFAULT)
								return(1);
	return (0);
}

char *next_line(char **line, int *fd, int *map_counter)
{
	char *l;
	free(*line);
	l = get_next_line(*fd);
	(*map_counter)++;
	return (l);
}

void print_struct(t_game *game)
{
	printf("%s\n", game->path.north);
	printf("%s\n", game->path.south);
	printf("%s\n", game->path.east);
	printf("%s\n", game->path.west);
	printf("%s\n", game->path.cealing);
	printf("%s\n", game->path.floor);
	int i = 0;
	while (i < game->path.height)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
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

void	free_rgb(char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

int	check_colors(t_game *game, char *color, t_rgb *colors)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(color, ',');
	while (rgb[i])
		i++;
	if (i != 3)
		print_error("Error! Wrong Colors!\n", game, 0);
	colors->r = ft_atoi(rgb[0]);
	colors->g = ft_atoi(rgb[1]);
	colors->b = ft_atoi(rgb[2]);
	if (colors->r < 0 || colors->r > 255
		|| colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
		print_error("Error! Wrong Colors!\n", game, 0);
	colors->hex = colors->r;
	colors->hex = (colors->hex << 8) + colors->g;
	colors->hex = (colors->hex << 8) + colors->b;
	free_rgb(rgb);
	return (1);
}

void check_params(t_game *game)
{
	if (!full_check(game))
		print_error("Error! wrong map!\n", game, 0);
	check_colors(game, game->path.cealing, &game->ceiling_color);
	check_colors(game, game->path.floor, &game->floor_color);
}

char	*skip_empty_lines(t_game *game, char *line, int *fd, int *map_counter)
{
	line = get_next_line(*fd);
	(*map_counter)++;
	while (line && line[0] == '\n')
		line = next_line(&line, fd, map_counter);
	if (line[0] == '\0')
		print_error("Error! Wrong map!\n", game, 0);
	return (line);
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

void	invalid_map_error(t_game *game, char *line)
{
	free (line);
	print_error("Error! Invalid Map!\n", game, 0);	
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

// int ft_empty(char *line)
// {
// 	int i;

// 	i = 0;
	
// }

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
				print_error("Error! wrong map!\n", game, 0);
		}
		x = game->path.width;
		i++;
	}
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
				print_error("Error! wrong map!\n", game, 0);
		}
		x = 0;
		i++;
	}
	check_right(game, map);
}

void	check_up_down(t_game *game, char **map)
{
	int x;

	x = 0;
	while (x < game->path.width - 1)
	{
		if (map[0][x] == ' ' || map[0][x] == '1')
			x++;
		else
			print_error("Error! wrong map!\n", game, 0);
	}
	x = 0;
	while (x < game->path.width - 1)
	{
		if (map[game->path.height - 1][x] == ' ' || map[game->path.height - 1][x] == '1')
			x++;
		else
			print_error("Error! wrong map!\n", game, 0);
	}
}

void	check_borders(t_game *game, char **map, int i, int x)
{
	if ((i - 1) >= 0)
		if ((map[i - 1][x] != ' ' && map[i - 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((x - 1) >= 0)
		if ((map[i][x - 1] != ' ' && map[i][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height)
		if ((map[i + 1][x] != ' ' && map[i + 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((x + 1) < game->path.width)
		if ((map[i][x + 1] != ' ' && map[i][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height && (x + 1) < game->path.width)
		if ((map[i + 1][x + 1] != ' ' && map[i + 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height && (x - 1) >= 0)
		if ((map[i + 1][x - 1] != ' ' && map[i + 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i - 1) >= 0 && (x + 1) < game->path.width)
		if ((map[i - 1][x + 1] != ' ' && map[i - 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i - 1) >= 0 && (x - 1) >= 0)
		if ((map[i - 1][x - 1] != ' ' && map[i - 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
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
		print_error("Error! invalid map input!\n", game, 0);
}
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

void check_args(t_game *game, int argc, const char **argv, int *fd)
{
	int map_counter;

	map_counter = 0;
    if (argc != 2 || check_exts((char *)argv[1]))
		print_error("Error! invalid or missing map!\n", game, 0);
	game->path.file_name = ft_strdup((char *)argv[1]);
	*fd = open(game->path.file_name, O_RDONLY);
    if (*fd == -1)
		print_error("Error! Wrong path!\n", game, 0);
	init_struct(game);
	if (!alloc_args(game, fd, &map_counter))
		print_error("missing map instructions!\n", game, 0);
	pop_map(game, fd, &map_counter);
	check_map(game, game->map);
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

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

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

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
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
		close_all(game, 0);
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

void	render_things(t_game *game)
{
	render_floor_ceiling(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img, 0, 0);
}

void	move_forward(t_game *game)
{
	if (game->map[(int)(game->mlx.pos_y)]
			[(int)(game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed)] != '1')
		game->mlx.pos_x += game->mlx.dir_x * game->moves.move_speed;
	if (game->map
		[(int)(game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed)]
		[(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y += game->mlx.dir_y * game->moves.move_speed;
}

void	move_side(t_game *game)
{
	if (game->map[(int)(game->mlx.pos_y)]
			[(int)(game->mlx.pos_x + game->mlx.plane_x * game->moves.move_side_speed)]
				!= '1')
		game->mlx.pos_x += game->mlx.plane_x * game->moves.move_side_speed;
	if (game->map
		[(int)(game->mlx.pos_y + game->mlx.plane_y * game->moves.move_side_speed)]
		[(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y += game->mlx.plane_y * game->moves.move_side_speed;
}

void	rotate_camera(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->mlx.dir_x;
	old_plane_x = game->mlx.plane_x;
	game->mlx.dir_x = game->mlx.dir_x * cos(game->moves.rot_speed)
		- game->mlx.dir_y * sin(game->moves.rot_speed);
	game->mlx.dir_y = old_dir_x * sin(game->moves.rot_speed)
		+ game->mlx.dir_y * cos(game->moves.rot_speed);
	game->mlx.plane_x = game->mlx.plane_x * cos(game->moves.rot_speed)
		- game->mlx.plane_y * sin(game->moves.rot_speed);
	game->mlx.plane_y = old_plane_x * sin(game->moves.rot_speed)
		+ game->mlx.plane_y * cos(game->moves.rot_speed);
}

int	game_loop(t_game *game)
{
	if (game->moves.w == 1 || game->moves.s == 1)
		move_forward(game);
	if (game->moves.a == 1 || game->moves.d == 1)
		move_side(game);
	if (game->moves.l == 1 || game->moves.r == 1)
		rotate_camera(game);
	render_things(game);
	return (0);
}

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

int main(int argc, char const *argv[])
{
    int fd;
    t_game *game;
    
	game = malloc(sizeof(t_game));
    check_args(game, argc, argv, &fd);
	// print_struct(game);
	init_game(game);
	close_all(game, 3);
    return (0);
}
