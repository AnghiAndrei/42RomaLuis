/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:06 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 17:17:13 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	game(t_master *master)
{
	print_map(master, 0);
	print_minimap(master->map, master);
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	master;

	if (argc != 2)
		return (printf("Error\nMarshal: Input error\n"));
	if (ceck_file(argv[1]) != 0 || game_init(&master,
			open(argv[1], O_RDONLY), NULL, ft_strjoin("\0", "\0")) != 0
		|| ceck_map(&master) != 0)
		return (free_all(&master), EXIT_FAILURE);
	master.pos_x = master.mxp + 0.5;
	master.pos_y = master.myp + 0.5;
	game_init5(&master);
	master.map[(int)(master.yp)][(int)(master.xp)] = '0';
	game(&master);
	mlx_loop_hook(master.mlx, &game, &master);
	mlx_hook(master.win, 2, 1L << 0, &controller, &master);
	mlx_hook(master.win, 6, 0, mause_controll, &master);
	mlx_hook(master.win, 17, 0, close_game, &master);
	mlx_loop(master.mlx);
	return (0);
}
