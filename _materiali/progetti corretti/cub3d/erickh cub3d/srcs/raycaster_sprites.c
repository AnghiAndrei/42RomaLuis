/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:07:26 by ebraho            #+#    #+#             */
/*   Updated: 2022/09/22 16:37:59 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	animate_door(t_things *things)
{
	int		i;
	t_door	*temp;

	i = 0;
	while (i < things->map->n_doors)
	{
		temp = things->map->doors + i;
		if (things->map->world_map[temp->pos.y][temp->pos.x] == DOOR0
			|| things->map->world_map[temp->pos.y][temp->pos.x] == DOOR9)
		{
			i++;
			continue ;
		}
		if (temp->status == 0)
			things->map->world_map[temp->pos.y][temp->pos.x]--;
		else
			things->map->world_map[temp->pos.y][temp->pos.x]++;
		i++;
	}
}

static int	game_loop(t_things *things)
{
	things->timestamp = get_timestamp(things->start);
	if (things->moves.w || things->moves.s)
		move_forward(things);
	if (things->moves.a || things->moves.d)
		move_side(things);
	if (things->moves.l || things->moves.r)
		rotate_camera(things);
	render_everything(things);
	if (things->timestamp - things->last_anim_exec > 250)
	{
		animate_door(things);
		things->last_anim_exec = things->timestamp;
	}
	return (0);
}

static void	set_direction(t_map *map, t_things *things)
{
	things->dir_x = 0;
	things->dir_y = 0;
	things->plane_x = 0;
	things->plane_y = 0;
	if (map->world_map[map->spawn_y][map->spawn_x] == WEST)
	{
		things->dir_x = -1;
		things->plane_y = 0.66;
	}
	else if (map->world_map[map->spawn_y][map->spawn_x] == EAST)
	{
		things->dir_x = 1;
		things->plane_y = -0.66;
	}
	else if (map->world_map[map->spawn_y][map->spawn_x] == NORD)
	{
		things->dir_y = -1;
		things->plane_x = -0.66;
	}
	else if (map->world_map[map->spawn_y][map->spawn_x] == SOUTH)
	{
		things->dir_y = 1;
		things->plane_x = 0.66;
	}
}

static void	set_things(t_map *map, t_things *things)
{
	things->pos_x = map->spawn_x + 0.5;
	things->pos_y = map->spawn_y + 0.5;
	things->data = malloc(sizeof(t_data));
	things->map = map;
	things->rot_speed = 0;
	things->move_speed = 0;
	things->last_anim_exec = 0;
	things->mlx = mlx_init();
	things->data->img = mlx_new_image(things->mlx, 640, 480);
	things->data->addr = mlx_get_data_addr(things->data->img,
			&things->data->bits_per_pixel, &things->data->line_length,
			&things->data->endian);
	things->window = mlx_new_window(things->mlx, 640, 480, "Cub3D");
}

int	init_raycasting(t_map *map)
{
	t_things	*things;
	int			y;

	things = malloc(sizeof(t_things));
	set_direction(map, things);
	set_things(map, things);
	mlx_put_image_to_window(things->mlx, things->window,
		things->data->img, 0, 0);
	if (!load_textures(things))
		return (0);
	render_everything(things);
	things->start.tv_sec = 0;
	things->start.tv_usec = 0;
	gettimeofday(&things->start, NULL);
	things->timestamp = 0;
	mlx_mouse_get_pos(things->window, &things->old_mouse_x, &y);
	mlx_hook(things->window, 2, 0, &handle_keypress, things);
	mlx_hook(things->window, 3, 0, &handle_keyrelease, things);
	mlx_hook(things->window, 17, 0, &click_cross, things);
	mlx_hook(things->window, 6, 0, &handle_mouse, things);
	mlx_loop_hook(things->mlx, &game_loop, things);
	mlx_loop(things->mlx);
	return (1);
}
