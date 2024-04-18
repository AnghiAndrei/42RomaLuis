/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:28:34 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/18 16:13:57 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	controlli(int char_p, t_master *m)
{
	if (char_p == M_KEY)
	{
		if (m->minimapp == 1)
			m->minimapp = 0;
		else
			m->minimapp = 1;
	}
	if (char_p == ESC_KEY)
		close_game(m);
}

int	controller(int char_p, t_master *m)
{
	if (char_p == W_KEY && m->map[(int)(m->yp - WS)][(int)(m->xp)] != '1')
		m->yp -= WS;
	else if (char_p == S_KEY && m->map[(int)(m->yp + WS + WSC)][(int)(m->xp)]
		!= '1')
		m->yp += WS;
	else if (char_p == A_KEY && m->map[(int)(m->yp)][(int)(m->xp - WS)] != '1')
		m->xp -= WS;
	else if (char_p == D_KEY && m->map[(int)(m->yp)][(int)(m->xp + WS + WSC)]
		!= '1')
		m->xp += WS;
	controlli(char_p, m);
	print_map(m, 0);
	print_minimap(m->map, m);
	return (1);
}
