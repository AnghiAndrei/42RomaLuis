/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:51:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 12:51:36 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	w(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player - 1][mlx->c_player] != '1'
		&& mlx->map[mlx->l_player - 1][mlx->c_player] != '2')
	{
		if (mlx->map[mlx->l_player][mlx->c_player] == 'X')
			mlx->map[mlx->l_player][mlx->c_player] = 'E';
		else if (mlx->map[mlx->l_player][mlx->c_player] == 'Y')
			mlx->map[mlx->l_player][mlx->c_player] = 'U';
		else
			mlx->map[mlx->l_player][mlx->c_player] = '0';
		mlx->l_player--;
		controls_move(mlx);
		mlx->move++;
		print_mosse(mlx);
	}
}

static void	s(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player + 1][mlx->c_player] != '1'
		&& mlx->map[mlx->l_player + 1][mlx->c_player] != '2')
	{
		if (mlx->map[mlx->l_player][mlx->c_player] == 'X')
			mlx->map[mlx->l_player][mlx->c_player] = 'E';
		else if (mlx->map[mlx->l_player][mlx->c_player] == 'Y')
			mlx->map[mlx->l_player][mlx->c_player] = 'U';
		else
			mlx->map[mlx->l_player][mlx->c_player] = '0';
		mlx->l_player++;
		controls_move(mlx);
		mlx->move++;
		print_mosse(mlx);
	}
}

static void	a(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player][mlx->c_player - 1] != '1'
		&& mlx->map[mlx->l_player][mlx->c_player - 1] != '2')
	{
		if (mlx->map[mlx->l_player][mlx->c_player] == 'X')
			mlx->map[mlx->l_player][mlx->c_player] = 'E';
		else if (mlx->map[mlx->l_player][mlx->c_player] == 'Y')
			mlx->map[mlx->l_player][mlx->c_player] = 'U';
		else
			mlx->map[mlx->l_player][mlx->c_player] = '0';
		mlx->c_player--;
		controls_move(mlx);
		mlx->move++;
		print_mosse(mlx);
	}
}

static void	d(t_mlx *mlx)
{
	if (mlx->map[mlx->l_player][mlx->c_player + 1] != '1'
		&& mlx->map[mlx->l_player][mlx->c_player + 1] != '2')
	{
		if (mlx->map[mlx->l_player][mlx->c_player] == 'X')
			mlx->map[mlx->l_player][mlx->c_player] = 'E';
		else if (mlx->map[mlx->l_player][mlx->c_player] == 'Y')
			mlx->map[mlx->l_player][mlx->c_player] = 'U';
		else
			mlx->map[mlx->l_player][mlx->c_player] = '0';
		mlx->c_player++;
		controls_move(mlx);
		mlx->move++;
		print_mosse(mlx);
	}
}

int	controller(int char_p, t_mlx *mlx)
{
	if (char_p == W_KEY || char_p == UP_KEY)
		w(mlx);
	else if (char_p == S_KEY || char_p == DOWN_KEY)
		s(mlx);
	else if (char_p == A_KEY || char_p == LEFT_KEY)
		a(mlx);
	else if (char_p == D_KEY || char_p == RIGHT_KEY)
		d(mlx);
	else if (char_p == ESC_KEY)
		vw(mlx);
	if (mlx->map[mlx->l_player][mlx->c_player] == 'X'
		&& mlx->coin_grab == mlx->coin_tot)
		win_napoletan(mlx);
	animasion(mlx);
	return (1);
}
