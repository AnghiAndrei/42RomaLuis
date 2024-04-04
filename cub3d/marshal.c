#include "cub3d.h"

int	ceck_file(char *file)
{
	int		fd;
	char	**p;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nMarshal: File not found / unreadable"));
	p = ft_split(file, '.');
	if (!(ft_strncmp(p[sizeof(p) / sizeof(char *)], "cub", 3) == 0
			&& ft_strncmp(file, "cub", 4) != 0))
	{
		perror("Error\nMarshal: File extension not .cub");
		exit(EXIT_FAILURE);
	}
}
