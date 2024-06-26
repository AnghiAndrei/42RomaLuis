/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:17:36 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/10 08:17:36 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	len_int(long long int n)
{
	long long int	res;

	res = 0;
	if (n < 0)
	{
		n = -n;
		res++;
	}
	if (n == 0)
		res = 1;
	while (n != 0)
	{
		n = n / 10;
		res++;
	}
	return (res);
}
