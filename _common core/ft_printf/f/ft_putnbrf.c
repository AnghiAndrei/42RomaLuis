/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:30:40 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/23 11:04:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbrf(long long int nbr)
{
	char			c;
	long long int	nbr2;

	nbr2 = nbr;
	if (nbr == -922337203685477580)
		write(1, "-922337203685477580", 20);
	else
	{
		if (nbr < 0)
		{
			write(1, "-", 1);
			nbr = -nbr;
		}
		if (nbr >= 10)
			ft_putnbrf(nbr / 10);
		c = nbr % 10 + '0';
		write(1, &c, 1);
	}
	return (len_int(nbr2));
}
