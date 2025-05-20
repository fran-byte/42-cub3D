/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:32:51 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:25:40 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initializes ray step directions and side distances
 *
 * Determines the direction to step in the grid (either +1 or -1)
 * and calculates the initial side distances in x and y.
 *
 * @param g Game structure
 * @param v Raycasting variables
 */
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

/**
 * @brief Initializes a ray for a given screen column
 *
 * Computes the ray direction based on player direction and camera plane,
 * maps the player's position to grid coordinates, and calculates
 * delta distances used in the DDA algorithm.
 *
 * @param g Game structure
 * @param x Screen column (pixel)
 * @param v Raycasting variables to initialize
 */
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
