/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:28:45 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 10:18:45 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	pos_line(char **map, char c)
{
	int		i;
	int		b;

	i = 0;
	while (map[i] != NULL)
	{
		b = 0;
		while (map[i][b] != '\0')
		{
			if (map[i][b] == c)
				return (i);
			b++;
		}
		i++;
	}
	perror("Marshal: Error\nNot found che char");
	exit(EXIT_FAILURE);
	return (0);
}

int	pos_col(int line, char **map, char c)
{
	int		i;

	i = 1;
	while (map[line][i] != '\0')
	{
		if (map[line][i] == c)
			return (i);
		i++;
	}
	perror("Marshal: Error\nNot found che char");
	exit(EXIT_FAILURE);
	return (0);
}

void	tot_bag(t_mlx *mlx)
{
	int		i;
	int		b;

	i = 0;
	mlx->coin_tot = 0;
	while (mlx->map[i] != NULL)
	{
		b = 0;
		while (mlx->map[i][b] != '\0')
		{
			if (mlx->map[i][b] == 'C')
				mlx->coin_tot++;
			b++;
		}
		i++;
	}
}

int	exist_char(t_mlx *mlx, char find)
{
	int		i;
	int		b;

	i = 1;
	while (mlx->map[i] != NULL)
	{
		b = 1;
		while (mlx->map[i][b + 1] != '\0' && mlx->map[i][b + 1] != '\n')
		{
			if (mlx->map[i][b] == find)
				return (1);
			b++;
		}
		i++;
	}
	return (0);
}
