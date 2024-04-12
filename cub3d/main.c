/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:06 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 10:38:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init3(t_master *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, 9 * 100, 9 * 100, "Quartieri spagnioli");
	m->walln = NULL;
	m->walls = NULL;
	m->walle = NULL;
	m->wallo = NULL;
	m->floor = NULL;
	m->cap = NULL;
	m->yp = 0;
	m->xp = 0;
}

static int	game_init2(t_master *m, char **t2)
{
	char		**t;

	t = ft_split(t2[0], ' ');
	free_matrix(t2);
	if (ft_mlen(t) != 2)
		return (printf("Error\nMarshal: Find space in heder input\n"));
	else if (ft_strncmp(t[0], "NO", 2) == 0)
		m->walln = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "SO", 2) == 0)
		m->walls = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "WE", 2) == 0)
		m->wallo = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "EA", 2) == 0)
		m->walle = mlx_xpm_file_to_image(m->mlx, t[1], &m->i, &m->j);
	else if (ft_strncmp(t[0], "F", 1) == 0)
		m->floor = ft_strjoin(t[1], "\0");
	else if (ft_strncmp(t[0], "C", 1) == 0)
		m->cap = ft_strjoin(t[1], "\0");
	else
		return (free_matrix(t), printf("Error\nMarshal: Unreconigde input\n"));
	free_matrix(t);
	return (0);
}

static int	game_init(t_master *m, int fd, char *line, char *str)
{
	game_init3(m);
	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, "\n", 1) != 0)
	{
		if (game_init2(m, ft_splitf(line, '\n')) != 0)
			break ;
		line = get_next_line(fd);
	}
	free(line);
	if (m->walln == NULL || m->walls == NULL || m->wallo == NULL
		|| m->walle == NULL || m->floor == NULL || m->cap == NULL)
		return (close(fd), printf("Error\nMarshal: Input error\n"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		str = ft_strjoin12f(str, line);
		line = get_next_line(fd);
	}
	close(fd);
	if (str[0] == '\0')
		return (free_all(m), printf("Error\nMarshal: No map found\n"));
	m->map = ft_splitf(str, '\n');
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	master;

	if (argc != 2)
		return (printf("Error\nMarshal: Input error\n"));
	if (ceck_file(argv[1]) != 0 || game_init(&master,
			open(argv[1], O_RDONLY), NULL, ft_strjoin("\0", "\0")) != 0
		|| ceck_map(&master, -1, 0) != 0)
		return (EXIT_FAILURE);
	mlx_hook(master.win, ON_DESTROY, 0, close_game, &master);
	mlx_hook(master.win, 2, 0, controller, &master);
	mlx_loop(master.mlx);
	return (0);
}
