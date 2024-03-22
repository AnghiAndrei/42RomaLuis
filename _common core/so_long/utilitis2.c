/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:19:32 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 10:19:32 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	config_mlx2(t_mlx *mlx)
{
	mlx->move = 0;
	mlx->coin_grab = 0;
	mlx->winp = 0;
	mlx->l_player = pos_line(mlx->map, 'P');
	mlx->c_player = pos_col(mlx->l_player, mlx->map, 'P');
	tot_bag(mlx);
}

void	replace(t_mlx *mlx, char find, char rep)
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
				mlx->map[i][b] = rep;
			b++;
		}
		i++;
	}
}

void	put_shadow(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player - 1][mlx->c_player] == '0')
		mlx->map[mlx->l_player - 1][mlx->c_player] = 'U';
	else if (mlx->map[mlx->l_player + 1][mlx->c_player] == '0')
		mlx->map[mlx->l_player + 1][mlx->c_player] = 'U';
	else if (mlx->map[mlx->l_player][mlx->c_player - 1] == '0')
		mlx->map[mlx->l_player][mlx->c_player - 1] = 'U';
	else if (mlx->map[mlx->l_player][mlx->c_player + 1] == '0')
		mlx->map[mlx->l_player][mlx->c_player + 1] = 'U';
}
