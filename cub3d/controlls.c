/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:28:34 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/11 11:58:10 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	controller(int char_p, t_master *master)
{
	printf("%c\n", char_p);
	if (char_p == W_KEY)
		; //su
	else if (char_p == S_KEY)
		; //giu
	else if (char_p == A_KEY)
		; //sinistra
	else if (char_p == D_KEY)
		; //destra
	else if (char_p == LEFT_KEY)
		; //sinistra visuale
	else if (char_p == RIGHT_KEY)
		; //destra visuale
	else if (char_p == ESC_KEY)
		close_game(master);
	return (1);
}
