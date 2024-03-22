/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:31 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/12 10:39:31 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	vw(t_mlx *mlx)
{
	write(1, "Vesuvio Wins", 12);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	close_win(void)
{
	write(1, "Vesuvio Wins", 12);
	exit(0);
	return (1);
}

int	controller2(int char_p, t_mlx *mlx)
{
	if (char_p == ESC_KEY)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (1);
}

void	win_napoletan(t_mlx *mlx)
{
	t_mlx	mlx2;

	write(1, "You ran away to Dubai", 21);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx2.mlx = mlx_init();
	mlx2.win = mlx_new_window(mlx2.mlx, 500, 200, "Win Napoli");
	mlx2.path = mlx_xpm_file_to_image(mlx2.mlx, "textures/win.xpm",
			&mlx2.i, &mlx2.j);
	mlx_put_image_to_window(mlx2.mlx, mlx2.win, mlx2.path, 0, 0);
	mlx_hook(mlx2.win, ON_DESTROY, 0, close_win, (void *)0);
	mlx_hook(mlx2.win, 2, 0, controller2, &mlx2);
	mlx_loop(mlx2.mlx);
}

int	animasion(t_mlx *mlx)
{
	if (mlx->move % 4 == 0)
	{
		mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "textures/E.xpm", &mlx->i,
				&mlx->j);
		replace(mlx, 'I', '0');
		put_shadow(mlx);
	}
	else if (mlx->move % 4 != 0)
	{
		mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "textures/E2.xpm", &mlx->i,
				&mlx->j);
		replace(mlx, 'U', 'I');
	}
	return (0);
}
