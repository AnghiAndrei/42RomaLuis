/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:51:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 11:58:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	controls_move(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player][mlx->c_player] == 'I')
		vw(mlx);
	if (mlx->map[mlx->l_player][mlx->c_player] == 'C')
		mlx->coin_grab++;
	if (mlx->map[mlx->l_player][mlx->c_player] == 'E')
		mlx->map[mlx->l_player][mlx->c_player] = 'X';
	else if (mlx->map[mlx->l_player][mlx->c_player] == 'U')
		mlx->map[mlx->l_player][mlx->c_player] = 'Y';
	else
		mlx->map[mlx->l_player][mlx->c_player] = 'P';
	if (mlx->map[mlx->l_player][mlx->c_player] == 'I')
		vw(mlx);
}
