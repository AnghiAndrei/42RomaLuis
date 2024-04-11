/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:18 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/10 17:14:25 by aanghi           ###   ########.fr       */
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
	mlx_destroy_window(master.mlx, master.win);
	free_matrix(master->maps);
	free(master->cap);
	free(master->floor);
}

int	close_game(t_master *master)
{
	printf(1, "	--GAME OVER--	");
	free_all(master);
	exit(0);
	return (1);
}
