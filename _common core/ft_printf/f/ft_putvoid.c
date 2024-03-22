/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:29:35 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/23 14:48:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putvoid(size_t n)
{
	char	string[20];
	int		i2;
	char	*hex_digits;
	int		res;

	hex_digits = "0123456789abcdef";
	if (n == 0)
		return (ft_putstr("0x0"));
	i2 = 0;
	while (n != 0)
	{
		string[i2++] = hex_digits[n % 16];
		n = n / 16;
	}
	string[i2++] = 'x';
	string[i2++] = '0';
	string[i2] = '\0';
	res = 0;
	i2--;
	while (i2 != -1)
		res += ft_putchar(string[i2--]);
	return (res);
}
