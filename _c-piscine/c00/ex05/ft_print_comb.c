/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:34:35 by aanghi            #+#    #+#             */
/*   Updated: 2023/10/26 19:17:02 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	contrprint(int primo, int secondo, int terzo);

void	ft_print_comb(void)
{
	int	primo;
	int	secondo;
	int	terzo;

	secondo = 0;
	terzo = 0;
	primo = 0;
	while (primo != 10)
	{
		secondo = 0;
		while (secondo != 10)
		{
			terzo = 0;
			while (terzo != 10)
			{
				contrprint(primo, secondo, terzo);
				terzo++;
			}
			secondo++;
		}
		primo++;
	}
}

void	contrprint(int primo, int secondo, int terzo)
{
	char	t;

	if (secondo > primo)
	{
		if (terzo > secondo)
		{
			t = (char)(primo + '0');
			write(1, &t, 1);
			t = (char)(secondo + '0');
			write(1, &t, 1);
			t = (char)(terzo + '0');
			write(1, &t, 1);
			if (primo != 7)
			{
				write(1, ", ", 2);
			}
		}
	}
}
