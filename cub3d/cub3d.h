#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

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

int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin12f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	free_matrix(char **m);
int		ceck_file(char *file);
int		ft_mlen(char **temp);
