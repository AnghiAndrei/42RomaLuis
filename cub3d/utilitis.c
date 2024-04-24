/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:18 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/24 11:00:15 by aanghi           ###   ########.fr       */
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

void	free_all(t_master *m)
{
	mlx_destroy_window(m->mlx, m->win);
	mlx_destroy_image(m->mlx, m->no2.img);
	mlx_destroy_image(m->mlx, m->no.img);
	mlx_destroy_image(m->mlx, m->so.img);
	mlx_destroy_image(m->mlx, m->we.img);
	mlx_destroy_image(m->mlx, m->ea.img);
	mlx_destroy_image(m->mlx, m->bg.img);
	mlx_destroy_image(m->mlx, m->mwall);
	mlx_destroy_image(m->mlx, m->mfloor);
	mlx_destroy_image(m->mlx, m->mplayer);
	free(m->mlx);
	free_matrix(m->map);
	if (m->cap != NULL)
		free(m->cap);
	if (m->floor != NULL)
		free(m->floor);
}

int	close_game(t_master *master)
{
	printf("	--GAME OVER--	\n");
	free_all(master);
	exit(0);
	return (1);
}

char	**copy_m(char **m)
{
	char	**cm;
	int		i;

	i = 0;
	cm = malloc((ft_mlen(m) + 1) * sizeof(char *));
	while (m[i] != NULL)
	{
		cm[i] = ft_strjoin(m[i], "\0");
		i++;
	}
	cm[i] = NULL;
	return (cm);
}
