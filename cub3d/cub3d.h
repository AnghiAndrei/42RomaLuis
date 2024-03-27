#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

typedef struct s_mlx
{
	char		**map;
	void		*mlx;
	void		*win;
	void		*walln;
	void		*walle;
	void		*wallo;
	void		*walls;
}				t_mlx;

int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	**ft_split(char const *s, char c);
void	ceck_file(char *file);
