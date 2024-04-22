/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:44:28 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/22 17:14:16 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9999999
# endif

# define HEIGHT 1620
# define WIDTH 3000

# define TEXWIDTH 64
# define TEXHEIGHT 64

# define ANI 42
# define ANIM 84

# define MG 15
# define MD 4

# define WS 0.10
# define WC .05
# define WC2 .01

# define W_KEY 119
# define A_KEY 97
# define M_KEY 109
# define D_KEY 100
# define S_KEY 115
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bxp;
	int				line_l;
	int				endian;
}				t_img;

typedef struct s_master
{
	char			**map;
	void			*mlx;
	void			*win;
	char			*floor;
	char			*cap;
	int				qi;
	int				minimapp;
	int				a;
	int				i;
	int				j;
	int				ic;
	float			xp;
	float			yp;
	float			mxp;
	float			myp;
	int				colc;
	int				colf;
	int				sp;
	int				xmause;

	struct s_img	wall;
	struct s_img	bg;

	char			*mfloor;
	char			*mplayer;
	char			*mwall;

	struct s_img	no2;
	struct s_img	no;
	struct s_img	so;
	struct s_img	we;
	struct s_img	ea;

	float			camera_x;
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_x;
	float			delta_y;
	float			w_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	float			wall_x;
	int				tex_x;
	int				tex_y;
	float			step;
	float			tex_pos;

	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}					t_master;

typedef struct s_point
{
	int			l;
	int			c;
}				t_point;

char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				game_init(t_master *m, int fd, char *line, char *str);
unsigned int	get_pixel(t_master *m, t_img *img, int x, int y);
void			set_img(t_img *i, char *path, t_master *m);
void			set_background(t_master *m, int y, int x);
int				mause_controll(int x, int y, t_master *m);
int				controller(int char_p, t_master *master);
void			print_minimap(char **map, t_master *m);
void			render_y(t_master *m, int x, int y);
char			*ft_strjoin12f(char *s1, char *s2);
char			*ft_strjoin1f(char *s1, char *s2);
char			*ft_strjoin2f(char *s1, char *s2);
char			**ft_split(char const *s, char c);
void			ft_strcpy(char *dest, char *src);
float			ternals(int b, float t, float f);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strlen(const char *string);
void			print_map(t_master *m, int x);
char			**ft_splitf(char *s, char c);
int				close_game(t_master *master);
int				pos_line(char **map, char c);
int				ft_atoi(const char *string);
int				ceck_map(t_master *master);
void			free_all(t_master *master);
void			game_init5(t_master *m);
char			*get_next_line(int fd);
void			free_matrix(char **m);
int				ceck_file(char *file);
int				ft_mlen(char **temp);
int				findn(char *buffer);
char			**copy_m(char **m);
#endif