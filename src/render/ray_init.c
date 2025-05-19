/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:32:51 by user              #+#    #+#             */
/*   Updated: 2025/05/18 18:15:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_ray_steps(t_game *g, t_ray_vars *v)
{
	if (v->ray_dir_x < 0)
	{
		v->step_x = -1;
		v->side_dist_x = (g->player.x - v->map_x) * v->delta_dist_x;
	}
	else
	{
		v->step_x = 1;
		v->side_dist_x = (v->map_x + 1.0 - g->player.x) * v->delta_dist_x;
	}
	if (v->ray_dir_y < 0)
	{
		v->step_y = -1;
		v->side_dist_y = (g->player.y - v->map_y) * v->delta_dist_y;
	}
	else
	{
		v->step_y = 1;
		v->side_dist_y = (v->map_y + 1.0 - g->player.y) * v->delta_dist_y;
	}
}

void init_ray(t_game *g, int x, t_ray_vars *v)
{
	v->camera_x = 2.0 * x / SCREEN_WIDTH - 1.0;
	v->ray_dir_x = g->player.dir_x + g->player.plane_x * v->camera_x;
	v->ray_dir_y = g->player.dir_y + g->player.plane_y * v->camera_x;
	v->map_x = (int)g->player.x;
	v->map_y = (int)g->player.y;
	v->delta_dist_x = fabs(1 / v->ray_dir_x);
	v->delta_dist_y = fabs(1 / v->ray_dir_y);
	init_ray_steps(g, v);
}
