/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:28:34 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/19 17:38:25 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	controlli(int char_p, t_master *m)
{
	if (char_p == D_KEY && m->map[(int)(m->myp)][(int)(m->mxp + WS + WSC)]
		!= '1')
	{
		m->mxp += WS;
		m->yp += WS;
	}
	if (char_p == M_KEY)
	{
		if (m->minimapp == 1)
			m->minimapp = 0;
		else
			m->minimapp = 1;
	}
	// if (char_p == LEFT_KEY)
	// 	;
	// if (char_p == RIGHT_KEY)
	// 	;
	if (char_p == ESC_KEY)
		close_game(m);
}

int	controller(int char_p, t_master *m)
{
	if (char_p == W_KEY && m->map[(int)(m->myp - WS)][(int)(m->mxp)] != '1')
	{
		m->myp -= WS;
		m->xp -= WS;
	}
	else if (char_p == S_KEY && m->map[(int)(m->myp + WS + WSC)][(int)(m->mxp)]
		!= '1')
	{
		m->myp += WS;
		m->xp += WS;
	}
	else if (char_p == A_KEY && m->map[(int)(m->myp)][(int)(m->mxp - WS)] != '1')
	{
		m->mxp -= WS;
		m->yp -= WS;
	}
	controlli(char_p, m);
	m->pos_x = m->xp + 0.5;
	m->pos_y = m->yp + 0.5;
	print_map(m, 0);
	print_minimap(m->map, m);
	return (1);
}
