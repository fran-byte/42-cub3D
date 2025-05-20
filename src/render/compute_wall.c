/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:45:37 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:23:45 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Computes the exact position on the wall that the ray hits
 *
 * Calculates where the wall was hit in the x or y axis and normalizes it to a
 * value between 0 and 1.
 *
 * @param g Game structure
 * @param v Raycasting variables
 * @param perp_dist Perpendicular distance from player to wall
 * @return Normalized wall impact position
 */
double compute_wall_impact_position(t_game *g, t_ray_vars *v, double perp_dist)
{
    double wall_x;

    if (v->side == 0)
        wall_x = g->player.y + perp_dist * v->ray_dir_y;
    else
        wall_x = g->player.x + perp_dist * v->ray_dir_x;
    wall_x -= floor(wall_x);
    return (wall_x);
}

/**
 * @brief Computes the X coordinate on the texture to sample
 *
 * Based on the wall impact position and ray direction, calculates the correct
 * horizontal texture coordinate, flipping if necessary.
 *
 * @param wall_x Normalized wall impact position
 * @param tex_width Width of the texture
 * @param v Raycasting variables
 * @return Texture X coordinate
 */
int compute_texture_x(double wall_x, int tex_width, t_ray_vars *v)
{
    int tex_x;

    tex_x = (int)(wall_x * (double)tex_width);
    if ((v->side == 0 && v->ray_dir_x > 0) ||
        (v->side == 1 && v->ray_dir_y < 0))
        tex_x = tex_width - tex_x - 1;
    return (tex_x);
}

/**
 * @brief Computes all wall rendering parameters for a given ray
 *
 * Calculates distance, wall height, draw start/end, texture coordinates, etc.
 *
 * @param g Game structure
 * @param ray Ray information structure to fill
 * @param v Raycasting variables
 */
void compute_wall_info(t_game *g, t_ray_info *ray, t_ray_vars *v)
{
    double perp_wall_dist;
    double wall_x;
    int tex_width;

    tex_width = TEX_WIDTH;
    if (v->side == 0)
        perp_wall_dist =
            (v->map_x - g->player.x + (1 - v->step_x) / 2) / v->ray_dir_x;
    else
        perp_wall_dist =
            (v->map_y - g->player.y + (1 - v->step_y) / 2) / v->ray_dir_y;
    ray->distance = perp_wall_dist;
    ray->wall_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
    ray->draw_start = -ray->wall_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->wall_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_end >= SCREEN_HEIGHT)
        ray->draw_end = SCREEN_HEIGHT - 1;
    wall_x = compute_wall_impact_position(g, v, ray->distance);
    ray->tex_x = compute_texture_x(wall_x, tex_width, v);
}

/**
 * @brief Determines the cardinal direction of the wall that was hit
 *
 * Based on the ray direction and which side (x/y) was hit.
 *
 * @param ray Ray information structure to set direction
 * @param v Raycasting variables
 */
void compute_wall_orientation(t_ray_info *ray, t_ray_vars *v)
{
    if (v->side == 0)
    {
        if (v->ray_dir_x > 0)
            ray->wall_dir = WEST;
        else
            ray->wall_dir = EAST;
    }
    else
    {
        if (v->ray_dir_y > 0)
            ray->wall_dir = NORTH;
        else
            ray->wall_dir = SOUTH;
    }
}
