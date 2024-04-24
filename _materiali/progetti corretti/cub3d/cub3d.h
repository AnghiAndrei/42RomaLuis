#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include "minilibx/mlx.h"
# include "mlx_linux/mlx.h"
# include <sys/time.h>
# include <math.h>
// # include <X11/keysym.h>
// # include <X11/X.h>

# define DEFAULT 0
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define WIDTH 256
# define HEIGHT 256

# define XK_w 119
# define XK_a 97
# define XK_s 115
# define XK_d 100
# define XK_Left 65361
# define XK_Right 65363


// game->map[i] == (i < game->path.height - 1)
// game->map[i][x] == (x < game->path.width - 1)

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
	int				hex;
}					t_rgb;

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*cealing;
	char			*floor;
	int				height;
	int				width;
	char			*file_name;
}					t_map;

typedef struct s_spawn
{
	char	direction;
	int		x;
	int		y;
}				t_spawn;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	t_img			img;
	t_img			ea;
	t_img			so;
	t_img			we;
	t_img			no;
	int				endian;
	int				old_mouse_x;
	struct timeval	start;
	long			timestamp;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;
} 			t_mlx;

typedef struct s_walls 
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	w_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_walls;

typedef struct s_moves 
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				l;
	int				r;
	double			move_speed;
	double			move_side_speed;
	double			rot_speed;
}	t_moves;

typedef struct s_game
{
	struct s_mlx	mlx;
	struct s_map	path;
	struct s_rgb	floor_color;
	struct s_rgb	ceiling_color;
	struct s_spawn	spawn;
	struct s_walls	walls_data;
	struct s_moves	moves;
	char			**map;
}					t_game;

typedef struct s_colors
{
	struct s_rgb	floor;
	struct s_rgb	ceiling;
}					t_colors;



void				check_args(t_game *game, int argc, const char **argv, int *fd);
int					check_exts(char *map);
void                init_struct(t_game *game);
int					alloc_args(t_game *game, int *fd, int *map_counter);
void				pop_map(t_game *game, int *fd, int *map_counter);
void				pop_args(char *line, t_game *game);
int					full_check(t_game *game);
void				check_params(t_game *game);
int					check_colors(t_game *game, char *color, t_rgb *colors);
char				*alloc_mtx(t_game *game, char *line, int *fd, int *map_counter);
char				*skip_empty_lines(t_game *game, char *line, int *fd, int *map_counter);
char				*next_line(char **line, int *fd, int *map_counter);
void				free_rgb(char **rgb);
void				invalid_map_error(t_game *game, char *line);
char				*realloc_line(char *line, int r);
void				realloc_map(t_game *game);
void				check_left_right(t_game *game, char **map);
void				check_up_down(t_game *game, char **map);
void				check_right(t_game *game, char **map);
void				check_borders(t_game *game, char **map, int i, int x);
void				check_map(t_game *game, char **map);
void				take_spawn(t_game *game, char c, int y, int x);

void				init_game(t_game *game);
void				set_vars(t_game *game);
void				set_pos(t_game *game);
void				get_addresses(t_game *game);
void				render_things(t_game *game);
void				render_floor_ceiling(t_game *game);
void				render_walls(t_game *game);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				set_data(t_walls *data, t_mlx *mlx, int x);
double				ft_double(int b, double t, double f);
void				check_distance(t_walls *data, char **map);
void				render_y(t_walls *data, t_mlx *mlx, int x);
unsigned int		get_pixel(t_img *img, int x, int y);

int					handle_keyrelease(int keycode, t_game *game);
int					handle_keypress(int keycode, t_game *game);
void				handle_movement(int keycode, t_game *game);
int					click_x(t_game *game);
int					print_error(char *str, t_game *game, int i);

#endif