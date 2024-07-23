/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:46:15 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 12:51:04 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	t_mlx	mlx;
	int		l;

	if (argc == 2)
	{
		l = 0;
		ceck_file(argv[1]);
		map = mod_map(get_matrix(argv[1], 1, &l), l, &mlx);
		config_mlx(&mlx, map);
		mlx.ml = l;
		print_map(map, &mlx);
		mlx_hook(mlx.win, ON_DESTROY, 0, close_win, (void *)0);
		mlx_hook(mlx.win, 2, 0, controller, &mlx);
		mlx_loop(mlx.mlx);
	}
	else
		write(1, "Marshal: Not enough arguments", 29);
	return (0);
}
