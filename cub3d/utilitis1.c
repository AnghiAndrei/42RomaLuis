/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:49:28 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/15 13:56:49 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pos_line(char **map, char c)
{
	int		i;
	int		b;

	i = 0;
	while (map[i] != NULL)
	{
		b = 0;
		while (map[i][b] != '\0')
		{
			if (map[i][b] == c)
				return (-1);
			b++;
		}
		i++;
	}
	return (0);
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
