/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:28:10 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/14 09:28:21 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_iterative_power(int nb, int power)
{
	int	i;

	if (nb == 0 && power == 0)
		return (1);
	if (power < 0)
		return (0);
	i = 1;
	while (power > 0)
	{
		i = i * nb;
		power--;
	}
	return (i);
}
