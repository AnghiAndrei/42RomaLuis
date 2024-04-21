/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:25:56 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 17:16:50 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init3(t_master *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "Quartieri spagnioli");
	m->no.img = NULL;
	m->so.img = NULL;
	m->we.img = NULL;
	m->ea.img = NULL;
	m->floor = NULL;
	m->cap = NULL;
	m->minimapp = 1;
	m->ic = 0;
	m->yp = 0;
	m->xp = 0;
	m->myp = 0;
	m->mxp = 0;
	m->mfloor = mlx_xpm_file_to_image(m->mlx, "textures/MF.xpm", &m->i, &m->j);
	m->mplayer = mlx_xpm_file_to_image(m->mlx, "textures/MP.xpm", &m->i, &m->j);
	m->mwall = mlx_xpm_file_to_image(m->mlx, "textures/MW.xpm", &m->i, &m->j);
	set_img(&m->no2, "textures/NO2.xpm", m);
	m->a = 0;
	m->xmause = 0;
	m->plane_x = 0;
	m->plane_y = 0;
	m->dir_x = 0;
	m->dir_y = 0;
	m->bg.img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->bg.addr = mlx_get_data_addr(m->bg.img, &m->bg.bxp,
			&m->bg.line_l, &m->bg.endian);
}

static int	game_init2(t_master *m, char **t2)
{
	char		**t;

	t = ft_split(t2[0], ' ');
	free_matrix(t2);
	if (ft_mlen(t) != 2)
		return (printf("Error\nMarshal: Find space in heder input\n"));
	else if (ft_strncmp(t[0], "NO", 2) == 0)
		set_img(&m->no, t[1], m);
	else if (ft_strncmp(t[0], "SO", 2) == 0)
		set_img(&m->so, t[1], m);
	else if (ft_strncmp(t[0], "WE", 2) == 0)
		set_img(&m->we, t[1], m);
	else if (ft_strncmp(t[0], "EA", 2) == 0)
		set_img(&m->ea, t[1], m);
	else if (ft_strncmp(t[0], "F", 1) == 0)
		m->floor = ft_strjoin(t[1], "\0");
	else if (ft_strncmp(t[0], "C", 1) == 0)
		m->cap = ft_strjoin(t[1], "\0");
	else
		return (free_matrix(t), printf("Error\nMarshal: Unreconigde input\n"));
	free_matrix(t);
	m->ic++;
	return (0);
}

static void	game_init4(t_master *m, int fd, char *line)
{
	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, "\n", 1) != 0)
	{
		if (game_init2(m, ft_splitf(line, '\n')) != 0)
			break ;
		line = get_next_line(fd);
	}
	free(line);
}

static int	get_color(t_master *m)
{
	char	**temp;

	temp = ft_split(m->cap, ',');
	if (ft_mlen(temp) != 3)
		return (free_matrix(temp), printf("Error\nMarshal: Error input\n"));
	m->colc = (0xFF << 24 | ft_atoi(temp[0]) << 16 | ft_atoi(temp[1]) << 8
			| ft_atoi(temp[2]) << 8);
	free_matrix(temp);
	temp = ft_split(m->floor, ',');
	if (ft_mlen(temp) != 3)
		return (free_matrix(temp), printf("Error\nMarshal: Error input\n"));
	m->colf = (0xFF << 24 | ft_atoi(temp[0]) << 16 | ft_atoi(temp[1]) << 8
			| ft_atoi(temp[2]) << 8);
	free_matrix(temp);
	return (0);
}

int	game_init(t_master *m, int fd, char *line, char *str)
{
	game_init3(m);
	game_init4(m, fd, NULL);
	if (m->ic != 6)
		game_init4(m, fd, NULL);
	if (m->no.img == NULL || m->so.img == NULL || m->we.img == NULL
		|| m->ea.img == NULL || m->floor == NULL || m->cap == NULL)
		return (close(fd), printf("Error\nMarshal: Input error\n"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		str = ft_strjoin12f(str, line);
		line = get_next_line(fd);
	}
	close(fd);
	if (str[0] == '\0')
		return (printf("Error\nMarshal: No map found\n"));
	m->map = ft_splitf(str, '\n');
	if (get_color(m) != 0)
		return (1);
	return (0);
}
