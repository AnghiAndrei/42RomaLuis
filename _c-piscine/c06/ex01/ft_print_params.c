/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:05:10 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/09 12:05:12 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		i;
	int		j;

	j = 1;
	if (argc > 1)
	{
		while (j != argc)
		{
			i = 0;
			while (argv[j][i] != '\0')
				i++;
			write(1, argv[j], i);
			write(1, "\n", 1);
			j++;
		}
	}
}
