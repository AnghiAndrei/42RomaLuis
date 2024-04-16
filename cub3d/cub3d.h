/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:44:28 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/16 17:36:38 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define MG 20
# define MD 4
# define WS 0.10
# define WSC 0.90

# define W_KEY 119
# define A_KEY 97
# define M_KEY 109
# define D_KEY 100
# define S_KEY 115
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307

typedef struct s_master
{
	char		**map;
	void		*mlx;
	void		*win;
	void		*walln;
	void		*walle;
	void		*wallo;
	void		*walls;
	char		*floor;
	char		*cap;
	char		*mfloor;
	char		*mplayer;
	char		*mwall;
	int			qi;
	int			minimapp;
	int			i;
	int			j;
	int			ic;
	float		xp;
	float		yp;
	int			colc;
	int			colf;
}				t_master;

typedef struct s_point
{
	int			l;
	int			c;
}				t_point;

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		game_init(t_master *m, int fd, char *line, char *str);
int		controller(int char_p, t_master *master);
char	*ft_strjoin12f(char *s1, char *s2);
void	print_minimap(char **map, t_master *m);
char	*ft_strjoin1f(char *s1, char *s2);
char	*ft_strjoin2f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_strcpy(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *string);
char	**ft_splitf(char *s, char c);
int		close_game(t_master *master);
int		pos_line(char **map, char c);
int		ft_atoi(const char *string);
int		ceck_map(t_master *master);
void	free_all(t_master *master);
char	*get_next_line(int fd);
void	print_map(t_master *m);
void	free_matrix(char **m);
int		ceck_file(char *file);
int		ft_mlen(char **temp);
int		findn(char *buffer);
char	**copy_m(char **m);
#endif