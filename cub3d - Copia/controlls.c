/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:28:34 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/15 17:30:37 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	controller(int char_p, t_master *m)
{
	if (char_p == W_KEY && m->map[(int)(m->yp)][(int)(m->xp - WS)] != '1')
		m->xp -= WS;
	else if (char_p == S_KEY && m->map[(int)(m->yp)][(int)(m->xp + WS)] != '1')
		m->xp += WS;
	else if (char_p == A_KEY && m->map[(int)(m->yp - WS)][(int)(m->xp)] != '1')
		m->yp -= WS;
	else if (char_p == D_KEY && m->map[(int)(m->yp + WS)][(int)(m->xp)] != '1')
		m->yp += WS;
	else if (char_p == LEFT_KEY)
		;
	else if (char_p == RIGHT_KEY)
		;
	else if (char_p == ESC_KEY)
		close_game(m);
	print_map(m->map, m);
	return (1);
}
