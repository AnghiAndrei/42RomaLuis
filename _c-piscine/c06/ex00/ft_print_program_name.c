/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:02:05 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/09 12:03:57 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		i;

	if (argc == 1)
	{
		i = 0;
		while (argv[0][i] != '\0')
			i++;
		write(1, argv[0], i);
		write(1, "\n", 1);
	}
}
