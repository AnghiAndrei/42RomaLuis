/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <aanghi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:31:05 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/22 12:31:44 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbru(unsigned int nbr)
{
	char		c;

	if (nbr >= 10)
		ft_putnbru(nbr / 10);
	c = nbr % 10 + '0';
	write(1, &c, 1);
	return (len_int(nbr));
}
