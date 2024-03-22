/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:28:09 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/23 13:31:07 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex(unsigned int n, int i)
{
	char	string[8];
	int		i2;
	char	*hex_digits;
	int		res;

	hex_digits = "0123456789ABCDEF";
	if (i == 2)
		hex_digits = "0123456789abcdef";
	if (n == 0)
		return (ft_putchar('0'));
	i2 = 0;
	while (n != 0)
	{
		string[i2++] = hex_digits[n % 16];
		n = n / 16;
	}
	res = 0;
	i2--;
	while (i2 != -1)
		res += ft_putchar(string[i2--]);
	return (res);
}
