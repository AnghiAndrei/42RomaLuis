#include "cub3d.h"

void	ceck_file(char *file)
{
	int		fd;
	char	**p;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nMarshal: File not found / unreadable");
		exit(EXIT_FAILURE);
	}
	p = ft_split(file, '.');
	if (!(ft_strncmp(p[sizeof(p) / sizeof(char *)], "ber", 3) == 0
			&& ft_strncmp(file, "ber", 4) != 0))
	{
		perror("Error\nMarshal: File extension not .ber");
		exit(EXIT_FAILURE);
	}
	ceck_map(file);
}
