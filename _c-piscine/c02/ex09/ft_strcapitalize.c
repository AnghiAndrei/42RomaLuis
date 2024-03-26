/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:55:41 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/03 12:48:30 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	cambia;

	i = 0;
	cambia = 1;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z' && cambia == 1)
			cambia = 0;
		else if (str[i] >= 'A' && str[i] <= 'Z' && cambia == 0)
			str[i] = str[i] + 32;
		if (str[i] >= 'a' && str[i] <= 'z' && cambia == 1)
		{
			str[i] = str[i] - 32;
			cambia = 0;
		}
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z')))
			cambia = 1;
		if (str[i] >= '0' && str[i] <= '9')
			cambia = 0;
		i++;
	}
	return (str);
}
