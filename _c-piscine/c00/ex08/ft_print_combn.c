/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:15:56 by aanghi            #+#    #+#             */
/*   Updated: 2023/10/30 10:05:29 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_combinations(int n, int m, int combination[], int index);

void	ft_print_combn(int n)
{
	int		combination[9];

	if (n > 0 && n < 10)
	{
		ft_print_combinations(n, 0, combination, 0);
	}
}

void	ft_print_combinations(int n, int m, int combination[], int index)
{
	int		i;
	char	digit;

	if (index == n)
	{
		i = 0;
		while (i < n)
		{
			digit = combination[i] + '0';
			write(1, &digit, 1);
			i++;
		}
		if (combination[0] != 10 - n)
		{
			write(1, ", ", 2);
		}
		return ;
	}
	i = m;
	while (i <= 9)
	{
		combination[index] = i;
		ft_print_combinations(n, i + 1, combination, index + 1);
		i++;
	}
}
