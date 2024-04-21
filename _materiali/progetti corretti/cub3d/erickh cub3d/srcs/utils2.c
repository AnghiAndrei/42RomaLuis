/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 00:47:39 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/23 01:00:41 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	next_line(char **line, int fd)
{
	free(*line);
	*line = get_next_line(fd);
}

void	free_colors(char **colors, char *str)
{
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	free(str);
}
