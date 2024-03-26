/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:00:03 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/01 14:08:46 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	setarray(char hex_digits[16]);

void	ft_putstr_non_printable(char *str)
{
	char			hex_digits[16];
	unsigned char	hex_digit1;
	unsigned char	hex_digit2;

	while (*str)
	{
		if (*str < 32 || *str > 126)
		{
			setarray(hex_digits);
			hex_digit1 = (*str >> 4) & 0xF;
			hex_digit2 = *str & 0xF;
			write(1, "\\", 1);
			write(1, &hex_digits[hex_digit1], 1);
			write(1, &hex_digits[hex_digit2], 1);
		}
		else
			write(1, str, 1);
		str++;
	}
}

void	setarray(char hex_digits[16])
{
	hex_digits[0] = '0';
	hex_digits[1] = '1';
	hex_digits[2] = '2';
	hex_digits[3] = '3';
	hex_digits[4] = '4';
	hex_digits[5] = '5';
	hex_digits[6] = '6';
	hex_digits[7] = '7';
	hex_digits[8] = '8';
	hex_digits[9] = '9';
	hex_digits[10] = 'a';
	hex_digits[11] = 'b';
	hex_digits[12] = 'c';
	hex_digits[13] = 'd';
	hex_digits[14] = 'e';
	hex_digits[15] = 'f';
}
