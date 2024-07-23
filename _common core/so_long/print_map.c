/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:28:06 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 12:20:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(char **map, t_mlx *mlx)
{
	int		i;
	int		b;

	i = 0;
	mlx_clear_window(mlx->mlx, mlx->win);
	while (map[i] != NULL)
	{
		b = 0;
		while (map[i][b] != '\0' && map[i][b] != '\n')
		{
			print_map_sup1(map, mlx, i, b);
			b++;
		}
		i++;
	}
}

void	print_map_sup1(char **map, t_mlx *mlx, int i, int b)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->path,
		b * 100, i * 100);
	if (map[i][b] == '1')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->wallnov,
			b * 100, i * 100);
	if (map[i][b] == 'C')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->bag,
			b * 100, i * 100);
	if (map[i][b] == 'P')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player,
			b * 100, i * 100);
	if (map[i][b] == 'E' && mlx->coin_grab == mlx->coin_tot)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->exit_open,
			b * 100, i * 100);
	if (map[i][b] == 'E' && mlx->coin_grab != mlx->coin_tot)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->exit,
			b * 100, i * 100);
	if (map[i][b] == 'X' && mlx->coin_grab == mlx->coin_tot)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->exit_open,
			b * 100, i * 100);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player,
			b * 100, i * 100);
	}
	print_map_sup2(map, mlx, i, b);
}

void	print_map_sup2(char **map, t_mlx *mlx, int i, int b)
{
	if (map[i][b] == 'F')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->exit_open,
			b * 100, i * 100);
	if (map[i][b] == 'X' && mlx->coin_grab != mlx->coin_tot)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->exit,
			b * 100, i * 100);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player,
			b * 100, i * 100);
	}
	if (map[i][b] == '2')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->wallv,
			b * 100, i * 100);
	if (map[i][b] == 'U')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->shadow,
			b * 100, i * 100);
	if (map[i][b] == 'I')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->fire,
			b * 100, i * 100);
	if (map[i][b] == 'Y')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->shadow,
			b * 100, i * 100);
	if (map[i][b] == 'Y')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player,
			b * 100, i * 100);
}

void	print_mosse(t_mlx *mlx)
{
	write(1, "Moves made: ", 12);
	ft_putnbr(mlx->move);
	write(1, "\n", 1);
	print_map(mlx->map, mlx);
	mlx_string_put(mlx->mlx, mlx->win, 5, 5, 1, "Moves made: ");
	mlx_string_put(mlx->mlx, mlx->win, 120, 5, 1, ft_itoa(mlx->move));
}
