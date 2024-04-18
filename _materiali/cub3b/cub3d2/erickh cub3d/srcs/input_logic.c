/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:02:37 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/22 16:32:32 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	find_nearest_door(t_things *things)
{
	double	min_dist;
	double	dist;
	int		i;
	t_door	*temp;

	min_dist = INT32_MAX;
	i = 0;
	while (i < things->map->n_doors)
	{
		dist = get_distance(things->pos_x, things->pos_y,
				things->map->doors[i].pos.x, things->map->doors[i].pos.y);
		if (dist < min_dist)
		{
			min_dist = dist;
			temp = things->map->doors + i;
		}
		i++;
	}
	temp->status = !temp->status;
	if (temp->status == 1)
		things->map->world_map[temp->pos.y][temp->pos.x]++;
	else
		things->map->world_map[temp->pos.y][temp->pos.x]--;
}

static void	handle_movement(int keycode, t_things *things)
{
	if (keycode == 13)
	{
		things->moves.w = 1;
		things->move_speed = .05;
	}
	if (keycode == 0)
	{
		things->moves.a = 1;
		things->move_side_speed = .05;
	}
	if (keycode == 1)
	{
		things->moves.s = 1;
		things->move_speed = -.05;
	}
	if (keycode == 2)
	{
		things->moves.d = 1;
		things->move_side_speed = -.05;
	}
}

int	handle_mouse(int x, int y, t_things *things)
{
	double	old_d;
	double	old_p;

	things->rot_speed = -6.2 / (SCREENWIDTH * 2);
	if (things->old_mouse_x != x)
	{
		old_d = things->dir_x;
		old_p = things->plane_x;
		things->rot_speed *= (things->old_mouse_x - x);
		things->dir_x = things->dir_x * cos(things->rot_speed)
			- things->dir_y * sin(things->rot_speed);
		things->dir_y = old_d * sin(things->rot_speed)
			+ things->dir_y * cos(things->rot_speed);
		things->plane_x = things->plane_x * cos(things->rot_speed)
			- things->plane_y * sin(things->rot_speed);
		things->plane_y = old_p * sin(things->rot_speed)
			+ things->plane_y * cos(things->rot_speed);
	}
	things->rot_speed = 0;
	if (x >= 0 && x <= SCREENWIDTH && y >= 0 && y <= SCREENHEIGHT)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	things->old_mouse_x = x;
	return (0);
}

int	handle_keypress(int keycode, t_things *things)
{
	if (keycode == 53)
		click_cross(keycode, things);
	handle_movement(keycode, things);
	if (keycode == 123)
	{
		things->moves.l = 1;
		things->rot_speed = -.05;
	}
	if (keycode == 124)
	{
		things->moves.r = 1;
		things->rot_speed = .05;
	}
	if (keycode == 14)
		find_nearest_door(things);
	return (1);
}

int	handle_keyrelease(int keycode, t_things *things)
{
	if (keycode == 13 || keycode == 1)
		things->move_speed = 0;
	if (keycode == 2 || keycode == 0)
		things->move_side_speed = 0;
	if (keycode == 13)
		things->moves.w = 0;
	if (keycode == 1)
		things->moves.s = 0;
	if (keycode == 2)
		things->moves.d = 0;
	if (keycode == 0)
		things->moves.a = 0;
	if (keycode == 123 || keycode == 124)
		things->rot_speed = 0;
	if (keycode == 123)
		things->moves.l = 0;
	if (keycode == 124)
		things->moves.r = 0;
	return (1);
}
