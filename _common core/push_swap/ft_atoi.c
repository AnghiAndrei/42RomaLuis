/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:37:02 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 14:37:48 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *string)
{
	int				i;
	long int		res;
	int				s;

	i = 0;
	if (ft_strncmp("-2147483648", string, 12) == 0)
		return (-2147483648);
	while (string[i] == ' ' || (string[i] >= 9 && string[i] <= 13))
		i++;
	s = 1;
	if (string[i] == '+' || string[i] == '-')
	{
		if (string[i] == '-')
			s = -1;
		i++;
	}
	res = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		res = (res * 10) + (string[i] - '0');
		i++;
	}
	if (res > 2147483647 || res < -2147483647 || string[i] != '\0')
		error_message();
	return ((int)res * s);
}
