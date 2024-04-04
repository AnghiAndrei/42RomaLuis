#include "cub3d.h"

static void	game_init3(t_master *m){
	master->mlx = mlx_init();
	m->walln = NULL;
	m->walls = NULL;
	m->walle = NULL;
	m->wallo = NULL;
	m->floor = NULL;
	m->cap = NULL;
}

static int	game_init2(t_master *m, char *line)
{
	char    **t;

	t = ft_split(line, ' ');
	free(line);
	if (ft_mlen(t) != 2)
		return (printf("Error\nMarshal: Find space in heder input\n"));
	else if (ft_strncmp(t[0], "NO", 3) == 0)
		m->walln = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "SO", 3) == 0)
		m->walls = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "WE", 3) == 0)
		m->wallo = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "EA", 3) == 0)
		m->walle = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "F", 3) == 0)
		m->floor = ft_strjoin(t[0], "\0");
	else if (ft_strncmp(t[0], "C", 3) == 0)
		m->cap = ft_strjoin(t[0], "\0");
	else
		return (free_matrix(t), printf("Error\nMarshal: Unreconigde input\n"));
	free_matrix(t);
	if (m->walln == NULL || m->walls == NULL || m->wallo == NULL
			|| m->walle == NULL || m->floor == NULL || m->cap == NULL)
		return (free_matrix(t), printf("Error\nMarshal: Missing input\n"));
	return (0);
}

static int	game_init(t_master *master, int fd, char *line, char *str)
{
	game_init3(master);
	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, "\n", 2) != 0)
	{
		if (game_init2(master, line) != 0)
			return (1);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		str = ft_strjoin12f(str, line);
		line = get_next_line(fd);
	}
	if (str == NULL)
		return (printf("Error\nMarshal: No map found\n"));
	master->map =ft_split(str, '\n');
	free(str);
	return (0);
}

int main(int argc, char **argv)
{
	t_master master;

	if (argc != 2)
		return (printf("Error\nMarshal: Input error\n"));
	if (ceck_file(argv[1]) != 0 && game_init(&master, open(argv[1]), NULL,
		NULL) != 0)
		return (EXIT_FAILURE);
	return (0);
}
