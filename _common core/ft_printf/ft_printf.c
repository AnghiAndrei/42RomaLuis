/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:30:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/19 10:30:13 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	control1(char c, va_list args)
{
	if (c == '+')
		return (ft_putsign(va_arg(args, int)));
	return (ft_putchar(c));
}

static int	control(char c, va_list args)
{
	if (c == '%')
		return (ft_putchar('%'));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 'd')
		return (ft_putnbrf(va_arg(args, int)));
	if (c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 1));
	if (c == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 2));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'u')
		return (ft_putnbru(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_putvoid(va_arg(args, size_t)));
	return (control1(c, args));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			i = i + control(*str, args);
		}
		else
		{
			ft_putchar(*str);
			i++;
		}
		str++;
	}
	va_end(args);
	return (i);
}
