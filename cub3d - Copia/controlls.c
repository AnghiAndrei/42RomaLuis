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

int	controller(int x, int y, t_master *m)
{
	(void)y;
	rotate_camera(m, cos(x - m->xmause), sin(x - m->xmause));
	m->xmause = x;
	return (1);
}

static void	rotate_camera(t_master *m, int cos, int sin)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = m->dir_x;
	old_plane_x = m->plane_x;
	m->dir_x = m->dir_x * cos - m->dir_y * sin;
	m->dir_y = old_dir_x * sin + m->dir_y * cos;
	m->plane_x = m->plane_x * cos - m->plane_y * sin;
	m->plane_y = old_plane_x * sin + m->plane_y * cos;
}

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
	if (char_p == LEFT_KEY)
		rotate_camera(m, COSP, SINP);
	if (char_p == RIGHT_KEY)
		rotate_camera(m, COSN, SINN);
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
	m->pos_x = m->xp;
	m->pos_y = m->yp;
	// print_map(m, 0);
	// print_minimap(m->map, m);
	return (1);
}
