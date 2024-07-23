/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:48:03 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 11:06:55 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

#define W_KEY 13
#define A_KEY 0
#define D_KEY 2
#define S_KEY 1
#define UP_KEY 126
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define DOWN_KEY 125
#define ESC_KEY 53
#define ON_DESTROY 17

typedef struct s_point
{
	int			l;
	int			c;
}				t_point;

typedef struct s_mlx
{
	char		**map;
	int			move;
	int			l_player;
	int			c_player;
	int			coin_grab;
	int			coin_tot;
	int			winp;
	int			v;
	int			ml;
	void		*mlx;
	void		*win;
	void		*path;
	void		*wallnov;
	void		*wallv;
	void		*bag;
	void		*player;
	void		*exit;
	void		*exit_open;
	void		*shadow;
	void		*fire;
	int			i;
	int			j;
}				t_mlx;

void	vw(t_mlx *mlx);
char	*ft_itoa(int n);
int		close_win(void);
void	ft_putnbr(int n);
void	tot_bag(t_mlx *mlx);
void	ceck_map(char *file);
void	ceck_file(char *file);
int		animasion(t_mlx *mlx);
int		open_file(char *file);
void	put_shadow(t_mlx *mlx);
void	config_mlx2(t_mlx *mlx);
void	print_mosse(t_mlx *mlx);
void	controls_move(t_mlx *mlx);
void	win_napoletan(t_mlx *mlx);
int		count(char *line, char c);
int		pos_line(char **map, char c);
void	ceck_obj(int p, int e, int c);
void	print_map(char **map, t_mlx *mlx);
int		exist_char(t_mlx *mlx, char find);
char	**ft_split(char const *s, char c);
void	config_mlx(t_mlx *mlx, char **map);
int		controller2(int char_p, t_mlx *mlx);
int		controller(int keycode, t_mlx *mlx);
int		move_playr(int keycode, t_mlx *mlx);
int		pos_col(int line, char **map, char c);
void	malloc_matrix_controll(char **matrix);
void	ceck_map_square(char *line, int n_line);
void	replace(t_mlx *mlx, char find, char rep);
char	**mod_map(char **map, int l, t_mlx *mlx);
char	**get_matrix_marshal(int n_line, int fd);
void	ceck_format(char *line, int i, int n_line);
void	ceck_path(int n_line, int fd, int e, int c);
char	**get_matrix(char *file, int i, int *n_line);
void	ceck_map_deep(int n_line, char *file, int p, int e);
void	print_map_sup2(char **map, t_mlx *mlx, int i, int b);
void	print_map_sup1(char **map, t_mlx *mlx, int i, int b);
void	convert_element(char **map, int l, int c, t_point cur);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
