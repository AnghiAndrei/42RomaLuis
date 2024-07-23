/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:26:04 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/05 12:54:53 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *dest, char *src)
{
	int		i;
	int		i2;

	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	i2 = 0;
	while (src[i2] != '\0')
	{
		src[i2] = src[i2 + i];
		i2++;
	}
	src[i2] = '\0';
}

int	findn(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (i * -1);
	i++;
	return (i);
}
