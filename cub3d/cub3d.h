/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:44:28 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 10:59:04 by aanghi           ###   ########.fr       */
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

# define W_KEY 13
# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53
# define ON_DESTROY 17

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
	int			qi;
	int			i;
	int			j;
	int			xp;
	int			yp;
}				t_master;

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ceck_map(t_master *master, int i, int i2);
int		controller(int char_p, t_master *master);
char	*ft_strjoin12f(char *s1, char *s2);
char	*ft_strjoin1f(char *s1, char *s2);
char	*ft_strjoin2f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_strcpy(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *string);
char	**ft_splitf(char *s, char c);
int		close_game(t_master *master);
void	free_all(t_master *master);
char	*get_next_line(int fd);
void	free_matrix(char **m);
int		ceck_file(char *file);
int		ft_mlen(char **temp);
int		findn(char *buffer);
#endif