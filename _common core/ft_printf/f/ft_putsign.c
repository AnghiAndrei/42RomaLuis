/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:30:27 by aanghi            #+#    #+#             */
/*   Updated: 2024/10/18 11:40:09 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putsign(int nbr)
{
	int		n;

	n = 0;
	if (nbr >= 0)
	{
		write(1, "+", 1);
		n++;
	}
	return (ft_putnbru(nbr) + n);
}
