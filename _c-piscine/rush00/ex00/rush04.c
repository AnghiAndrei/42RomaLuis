/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:57:13 by aanghi            #+#    #+#             */
/*   Updated: 2023/10/28 12:57:18 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rush(int x, int y);
void	print_quadrato(int x2, int y2, int x, int y);

void	rush(int x, int y)
{
	int	x2;
	int	y2;

	x--;
	y--;
	y2 = 0;
	while (y2 <= y)
	{
		x2 = 0;
		while (x2 <= x)
		{
			print_quadrato(x2, y2, x, y);
			x2++;
		}
		y2++;
		write(1, "\n", 1);
	}
}

void	print_quadrato(int x2, int y2, int x, int y)
{
	if ((x2 == x && y2 == 0) || (x2 == 0 && y2 == y))
	{
		write(1, "C", 1);
	}
	else if ((x2 == 0 && y2 == 0) || (x2 == x && y2 == y))
	{
		write(1, "A", 1);
	}
	else if ((x2 == 0 || x2 == x) && (y2 != y && y2 != 0))
	{
		write(1, "B", 1);
	}
	else if ((y2 == 0 && x2 != x && x2 != 0) || (y2 == y && x2 != x && x2 != 0))
	{
		write(1, "B", 1);
	}
	else
	{
		write(1, " ", 1);
	}
}
