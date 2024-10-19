/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:29:00 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/19 10:29:00 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *string);
int		len_int(long long n);
int		ft_putstr(char *s);
int		ft_putvoid(size_t n);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putnbru(unsigned int nbr);
int		ft_putnbrf(long long int nbr);
int		ft_puthex(unsigned int n, int i);
int		ft_putsign(int nbr);
int		ft_printf(const char *str, ...);
