/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:43:59 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 13:00:29 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ceck_map_square(char *line, int n_line)
{
	if (ft_strlen(line) - 1 == n_line)
	{
		perror("Error\nMarshal: Map can't be a square");
		exit(EXIT_FAILURE);
	}
}

void	convert_element(char **map, int l, int c, t_point cur)
{
	if (cur.l < 0 || cur.l >= l || cur.c < 0 || cur.c >= c
		|| map[cur.l][cur.c] == '1' || map[cur.l][cur.c] == '-')
		return ;
	map[cur.l][cur.c] = '-';
	convert_element(map, l, c, (t_point){cur.l - 1, cur.c});
	convert_element(map, l, c, (t_point){cur.l + 1, cur.c});
	convert_element(map, l, c, (t_point){cur.l, cur.c - 1});
	convert_element(map, l, c, (t_point){cur.l, cur.c + 1});
}

char	**get_matrix_marshal(int n_line, int fd)
{
	char	**map;
	int		i;

	map = malloc((n_line + 1) * sizeof(char *));
	malloc_matrix_controll(map);
	map[0] = get_next_line(fd);
	i = 1;
	while (i != n_line)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}
