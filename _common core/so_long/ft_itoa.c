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

#include "so_long.h"

static int	len_int(int n)
{
	int		res;

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

static void	f1(int li, int n, char *s)
{
	int		i;

	i = li - 1;
	while (n != 0)
	{
		s[i--] = (n % 10) + '0';
		n = n / 10;
	}
}

static char	*min_int(void)
{
	char	*s;

	s = (char *)malloc(12);
	if (s == NULL)
		return (NULL);
	s[0] = '-';
	s[1] = '2';
	s[2] = '1';
	s[3] = '4';
	s[4] = '7';
	s[5] = '4';
	s[6] = '8';
	s[7] = '3';
	s[8] = '6';
	s[9] = '4';
	s[10] = '8';
	s[11] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		li;
	char	*s;
	int		ne;

	li = len_int(n);
	if (n == -2147483648)
		return (min_int());
	s = (char *)malloc(li + 1);
	if (s == NULL)
		return (NULL);
	ne = 0;
	if (n < 0)
	{
		n = -n;
		ne++;
	}
	if (n == 0)
		s[0] = '0';
	f1(li, n, s);
	if (ne == 1)
		s[0] = '-';
	s[li] = '\0';
	return (s);
}
