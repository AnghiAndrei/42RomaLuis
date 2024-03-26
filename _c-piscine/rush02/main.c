/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:33:35 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 20:33:36 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "zz_logic.h"
#include "parser.h"
#include "parser_b.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
		convert_to_ascii(argv[1], "numbers.dict");
	else if (argc == 3)
		convert_to_ascii(argv[2], argv[1]);
	else if (argc == 1)
	{
		return (0);
	}
	return (0);
}
