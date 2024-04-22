/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:28:34 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/22 17:05:27 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_camera(t_master *m, float cos2, float sin2)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = m->dir_x;
	old_plane_x = m->plane_x;
	m->dir_x = m->dir_x * cos2 - m->dir_y * sin2;
	m->dir_y = old_dir_x * sin2 + m->dir_y * cos2;
	m->plane_x = m->plane_x * cos2 - m->plane_y * sin2;
	m->plane_y = old_plane_x * sin2 + m->plane_y * cos2;
}

int	mause_controll(int x, int y, t_master *m)
{
	(void)y;
	if (m->xmause != 42000)
	{
		if (x - m->xmause < 0)
			rotate_camera(m, cos((WC2 * m->sp)), sin((WC2 * m->sp)));
		else
			rotate_camera(m, cos((-WC2 * m->sp)), sin((-WC2 * m->sp)));
	}
	m->xmause = x;
	return (0);
}

static void	move(t_master *m, int i, int d)
{
	if (i == 0)
	{
		if (m->map[(int)(m->yp)][(int)(m->xp + m->dir_x * (WS * d))] != '1')
			m->xp += m->dir_x * (WS * d);
		if (m->map[(int)(m->yp + m->dir_y * (WS * d))][(int)(m->xp)] != '1')
			m->yp += m->dir_y * (WS * d);
	}
	if (i == 1)
	{
		if (m->map[(int)(m->yp)][(int)(m->xp + m->plane_x * (WS * d))] != '1')
			m->xp += m->plane_x * (WS * d);
		if (m->map[(int)(m->yp + m->plane_y * (WS * d))][(int)(m->xp)] != '1')
			m->yp += m->plane_y * (WS * d);
	}
}

static void	controlli(int char_p, t_master *m)
{
	if (char_p == D_KEY)
	{
		m->mxp += WS;
		move(m, 1, -1);
	}
	if (char_p == M_KEY)
	{
		if (m->minimapp == 1)
			m->minimapp = 0;
		else
			m->minimapp = 1;
	}
	if (char_p == LEFT_KEY)
		rotate_camera(m, cos((WC2 * m->sp)), sin((WC2 * m->sp)));
	if (char_p == RIGHT_KEY)
		rotate_camera(m, cos((-WC2 * m->sp)), sin((-WC2 * m->sp)));
	if (char_p == ESC_KEY)
		close_game(m);
}

int	controller(int char_p, t_master *m)
{
	if (char_p == W_KEY)
	{
		m->myp -= WS;
		move(m, 0, 1);
	}
	else if (char_p == S_KEY)
	{
		m->myp += WS;
		move(m, 0, -1);
	}
	else if (char_p == A_KEY)
	{
		m->mxp -= WS;
		move(m, 1, 1);
	}
	controlli(char_p, m);
	return (1);
}
