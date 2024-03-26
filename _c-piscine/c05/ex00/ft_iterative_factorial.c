/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:25:12 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/14 09:25:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_iterative_factorial(int nb)
{
	int	r;

	r = 1;
	if (nb > 0)
	{
		while (nb != 1)
		{
			r = r * nb;
			nb--;
		}
		return (r);
	}
	else if (nb == 0)
		return (1);
	return (0);
}
