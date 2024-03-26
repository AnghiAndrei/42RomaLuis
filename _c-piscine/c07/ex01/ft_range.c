/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:21:52 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/15 16:21:55 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	*ft_range(int min, int max)
{
	int	*array;
	int	i;

	if (max <= min)
	{
		array = (int *)malloc(sizeof(int));
		*array = 0;
		return (array);
	}
	array = (int *)malloc((max - min) * sizeof(int));
	i = 0;
	while (i < (max - min))
	{
		array[i] = min + i;
		i++;
	}
	return (array);
}
