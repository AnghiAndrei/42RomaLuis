/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:11:23 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/23 17:27:33 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define WIDTH 256
# define HEIGHT 256
# define EMPTY 48
# define WALL 49
# define NORD 78
# define SOUTH 83
# define WEST 87
# define EAST 69
# define SPACE 32
# define DOOR_PATH "assets/door_0.png"
# define DOOR0 97
# define DOOR1 98
# define DOOR2 99
# define DOOR3 100
# define DOOR4 101
# define DOOR5 102
# define DOOR6 103
# define DOOR7 104
# define DOOR8 105
# define DOOR9 106
# define DOORFRAMES 10

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
}	t_color;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_textures {
	t_data	*ea;
	t_data	*no;
	t_data	*so;
	t_data	*we;
	t_data	*door[10];
}	t_textures;

typedef struct s_int_pos {
	int	x;
	int	y;
}	t_int_pos;

// Status 0 = closed/closing, 1 = opened/opening
typedef struct s_door {
	t_int_pos	pos;
	int			status;
}	t_door;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*str_floor;
	char	*str_ceilling;
	t_color	floor;
	t_color	ceilling;
	char	*str_map;
	char	**world_map;
	int		spawn_x;
	int		spawn_y;
	int		n_doors;
	t_door	*doors;
	int		max_x;
	int		max_y;
}	t_map;

typedef struct s_moves {
	int	w;
	int	s;
	int	a;
	int	d;
	int	l;
	int	r;
}	t_moves;

typedef struct s_things {
	void			*mlx;
	void			*window;
	t_data			*data;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			pos_x;
	double			pos_y;
	double			move_speed;
	double			move_side_speed;
	double			rot_speed;
	int				old_mouse_x;
	struct timeval	start;
	long			timestamp;
	long			last_anim_exec;
	t_moves			moves;
	t_map			*map;
	t_textures		*textures;
}	t_things;

typedef struct s_walls_data {
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
}	t_walls_data;

int				init_raycasting(t_map *map);
int				check_doors(t_map *textures, int i, int j);
int				check_map_content(t_map	*textures);
int				check_border1(t_map *textures, int i, int j);
int				check_border2(t_map *textures, int i, int j);
int				check_border3(t_map *textures, int i, int j);
int				check_border4(t_map *textures, int i, int j);
int				check_angle1(t_map *textures, int i, int j);
int				check_angle2(t_map *textures, int i, int j);
int				check_angle3(t_map *textures, int i, int j);
int				check_angle4(t_map *textures, int i, int j);
void			get_spawn_position(t_map *textures, int i, int j);
int				check_textures(t_map *textures);
int				parse_textures(char *line, t_map *textures);
double			get_distance(int x1, int y1, int x2, int y2);
int				print_error(char *str);
int				str_to_color(char *str, t_color *color);
void			sort_doors(t_map *textures, int x, int y);
int				check_doors(t_map *textures, int i, int j);
int				check_map(char *line, t_map *textures);
int				check_map_content(t_map	*textures);
int				check_textures(t_map *textures);
int				check_params(int argc, char **argv, int *fd);
void			get_spawn_position(t_map *textures, int i, int j);
int				parse_map(char **line, t_map *textures, int fd);
void			set_max_positions(t_map *map);
void			load_doors(t_map *map);
unsigned int	get_pixel(t_data *img, int x, int y);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			update_minimap(t_things *things);
int				handle_mouse(int x, int y, t_things *things);
int				handle_keypress(int keycode, t_things *things);
int				handle_keyrelease(int keycode, t_things *things);
int				load_textures(t_things *things);
long			get_timestamp(struct timeval start);
double			f_t(int b, double t, double f);
void			render_skybox(t_things *things);
void			setup_walls_data(t_walls_data *data, t_things *things, int x);
void			render_walls(t_things *things);
void			render_sprites(t_things *things);
void			render_everything(t_things *things);
void			move_forward(t_things *things);
void			move_side(t_things *things);
void			rotate_camera(t_things *things);
int				click_cross(int keycode, t_things *things);
void			next_line(char **line, int fd);
void			free_colors(char **colors, char *str);

#endif
