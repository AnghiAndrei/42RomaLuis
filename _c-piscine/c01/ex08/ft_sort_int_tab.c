/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:15:51 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/01 16:04:18 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int		temp;
	int		swapped;
	int		i2;

	swapped = 0;
	while (!(swapped))
	{
		i2 = 0;
		swapped = 1;
		while (i2 < size - 1)
		{
			if (tab[i2] > tab[i2 + 1])
			{
				temp = tab[i2];
				tab[i2] = tab[i2 + 1];
				tab[i2 + 1] = temp;
				swapped = 0;
			}
			i2++;
		}
	}
}
