/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:55:28 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/05 22:55:31 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	conv_char_to_int(char *n);

int	elimina_combo(char *argv)
{
	int	somma;
	int	i;

	i = 0;
	while (i != 12)
	{
		somma = conv_char_to_int(&argv[i]) + conv_char_to_int(&argv[i + 4]);
		if (!(somma >= 3 && somma <= 5) || !(argv[i] >= '0' && argv[i] < '5')
			|| !(argv[i + 4] >= '0' && argv[i + 4] < '5'))
			return (1);
		i++;
	}
	return (0);
}

int	conv_char_to_int(char *n)
{
	if (*n >= '0' && *n < '5')
		return (*n - '0');
	return (1);
}
