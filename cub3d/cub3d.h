#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mlx/mlx.h"

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
}				t_master;

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin12f(char *s1, char *s2);
char	*ft_strjoin1f(char *s1, char *s2);
char	*ft_strjoin2f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_strcpy(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *string);
char	**ft_splitf(char *s, char c);
char	*get_next_line(int fd);
void	free_matrix(char **m);
int		ceck_file(char *file);
int		ft_mlen(char **temp);
int		findn(char *buffer);
#endif