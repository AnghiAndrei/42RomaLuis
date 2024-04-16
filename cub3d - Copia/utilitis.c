/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:18 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/15 16:32:58 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mlen(char **temp)
{
	int		i;

	i = 0;
	while (temp[i] != NULL)
		i++;
	return (i);
}

void	free_matrix(char **m)
{
	int		i;

	if (m == NULL)
		return ;
	if (m != NULL)
	{
		i = 0;
		while (m[i] != NULL)
		{
			free(m[i]);
			m[i] = NULL;
			i++;
		}
		free(m);
		m = NULL;
	}
}

void	free_all(t_master *master)
{
	mlx_destroy_window(master->mlx, master->win);
	free_matrix(master->map);
	free(master->cap);
	free(master->floor);
}

int	close_game(t_master *master)
{
	printf("	--GAME OVER--	\n");
	free_all(master);
	exit(0);
	return (1);
}

// void	print_map(char **map, t_master *m)
// {
// 	int		i;
// 	int		b;

// 	i = -1;
// 	mlx_clear_window(m->mlx, m->win);
// 	while (map[++i] != NULL)
// 	{
// 		b = -1;
// 		while (map[i][++b] != '\0')
// 		{
// 			if (map[i][b] == '1')
// 				mlx_put_image_to_window(m->mlx, m->win, m->mwall,
// 					b * MG, i * MG);
// 			if (map[i][b] == '0')
// 				mlx_put_image_to_window(m->mlx, m->win, m->mfloor,
// 					b * MG, i * MG);
// 		}
// 	}
// 	mlx_put_image_to_window(m->mlx, m->win, m->mplayer, m->yp * MG, m->xp * MG);
// }
