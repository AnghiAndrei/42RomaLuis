/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/10 14:33:59 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ceck_file(char *file)
{
	char	**p;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nMarshal: File not found / unreadable\n", 44));
	p = ft_split(file, '.');
	i = 0;
	while (p[i + 1] != NULL)
		i++;
	if (!(ft_strncmp(p[i], "cub", 3) == 0
			&& ft_strncmp(file, "cub", 4) != 0))
		return (free_matrix(p),
			write(2, "Error\nMarshal: File extension not .cub\n", 39));
	free_matrix(p);
	return (0);
}
