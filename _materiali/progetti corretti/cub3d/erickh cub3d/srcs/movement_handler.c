/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:55:43 by pcoletta          #+#    #+#             */
/*   Updated: 2022/09/23 04:41:01 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_things *things)
{
	if (things->map->world_map[(int)(things->pos_y)]
			[(int)(things->pos_x + things->dir_x * things->move_speed)] != WALL
			&& things->map->world_map[(int)(things->pos_y)]
				[(int)(things->pos_x + things->dir_x * things->move_speed)]
					!= DOOR0)
		things->pos_x += things->dir_x * things->move_speed;
	if (things->map->world_map
		[(int)(things->pos_y + things->dir_y * things->move_speed)]
		[(int)(things->pos_x)] != WALL
		&& things->map->world_map
		[(int)(things->pos_y + things->dir_y * things->move_speed)]
		[(int)(things->pos_x)]
				!= DOOR0)
		things->pos_y += things->dir_y * things->move_speed;
}

void	move_side(t_things *things)
{
	if (things->map->world_map[(int)(things->pos_y)]
			[(int)(things->pos_x + things->plane_x * things->move_side_speed)]
				!= WALL
			&& things->map->world_map[(int)(things->pos_y)]
				[(int)(things->pos_x + things->dir_x * things->move_side_speed)]
					!= DOOR0)
		things->pos_x += things->plane_x * things->move_side_speed;
	if (things->map->world_map
		[(int)(things->pos_y + things->plane_y * things->move_side_speed)]
		[(int)(things->pos_x)] != WALL
		&& things->map->world_map[(int)(things->pos_y)]
			[(int)(things->pos_x + things->dir_x * things->move_side_speed)]
			!= DOOR0)
		things->pos_y += things->plane_y * things->move_side_speed;
}

void	rotate_camera(t_things *things)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = things->dir_x;
	old_plane_x = things->plane_x;
	things->dir_x = things->dir_x * cos(things->rot_speed)
		- things->dir_y * sin(things->rot_speed);
	things->dir_y = old_dir_x * sin(things->rot_speed)
		+ things->dir_y * cos(things->rot_speed);
	things->plane_x = things->plane_x * cos(things->rot_speed)
		- things->plane_y * sin(things->rot_speed);
	things->plane_y = old_plane_x * sin(things->rot_speed)
		+ things->plane_y * cos(things->rot_speed);
}
