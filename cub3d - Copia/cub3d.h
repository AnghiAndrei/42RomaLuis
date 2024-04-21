/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:44:28 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 17:15:24 by aanghi           ###   ########.fr       */
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

# define TEXWIDTH 100
# define TEXHEIGHT 100

# define MG 15
# define MD 4
# define WS 0.10
# define WSC 0.70

# define COSP cos(0.05)
# define SINP sin(0.05)
# define COSN cos(-0.05)
# define SINN sin(-0.05)

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
	char			*mfloor;
	char			*mplayer;
	char			*mwall;
	int				qi;
	int				minimapp;
	int				i;
	int				j;
	int				ic;
	int				xmause;
	double			xp;
	double			yp;
	double			mxp;
	double			myp;
	int				colc;
	int				colf;

	struct s_img	wall;
	struct s_img	bg;

	struct s_img	no2;
	struct s_img	no;
	struct s_img	so;
	struct s_img	we;
	struct s_img	ea;

	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_x;
	double			delta_y;
	double			w_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;

	double			dir_x;
	double			dir_y;
	double			pos_x;
	double			pos_y;
	double			plane_x;
	double			plane_y;
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
int				controller(int char_p, t_master *master);
void			print_minimap(char **map, t_master *m);
char			*ft_strjoin12f(char *s1, char *s2);
double			ternals(int b, double t, double f);
char			*ft_strjoin1f(char *s1, char *s2);
char			*ft_strjoin2f(char *s1, char *s2);
char			**ft_split(char const *s, char c);
void			ft_strcpy(char *dest, char *src);
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