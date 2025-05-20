/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:39:22 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:17:51 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Checks if a map position contains a wall
 *
 * Verifies if the specified coordinates are within map bounds and whether
 * they contain a wall ('1'). Used for collision detection in movement.
 *
 * @param g Game structure containing map data
 * @param x X coordinate to check
 * @param y Y coordinate to check
 * @return int 1 if position is a wall or out of bounds, 0 otherwise
 */
static int	is_wall(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= g->map.height_map
		|| map_x >= (int)ft_strlen(g->map.map[map_y]))
		return (1);
	if (g->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

/**
 * @brief Safely updates player position with collision checking
 *
 * Moves the player to new coordinates only if the target position isn't a wall.
 * Updates both the temporary and permanent player position coordinates.
 *
 * @param g Game structure
 * @param new_x Proposed new X coordinate
 * @param new_y Proposed new Y coordinate
 */
static void	safe_move(t_game *g, double new_x, double new_y)
{
	if (!is_wall(g, new_x, g->player.y))
		g->player.x = new_x;
	if (!is_wall(g, g->player.x, new_y))
		g->player.y = new_y;
	g->player.player_x = g->player.x;
	g->player.player_y = g->player.y;
}

/**
 * @brief Moves player forward along current direction vector
 *
 * Calculates movement using player's direction vector and MOVE_SPEED,
 * then updates position if movement is valid.
 *
 * @param g Game structure
 */
void	move_forward(t_game *g)
{
	double	move_x;
	double	move_y;

	move_x = g->player.dir_x * MOVE_SPEED;
	move_y = g->player.dir_y * MOVE_SPEED;
	safe_move(g, g->player.x + move_x, g->player.y + move_y);
	render_frame(g);
}

/**
 * @brief Moves player backward (opposite current direction)
 *
 * Calculates movement using inverted direction vector and MOVE_SPEED,
 * then updates position if movement is valid.
 *
 * @param g Game structure
 */
void	move_backward(t_game *g)
{
	double	move_x;
	double	move_y;

	move_x = -g->player.dir_x * MOVE_SPEED;
	move_y = -g->player.dir_y * MOVE_SPEED;
	safe_move(g, g->player.x + move_x, g->player.y + move_y);
	render_frame(g);
}

/**
 * @brief Strafe player left (perpendicular to current direction)
 *
 * Uses camera plane vector for left strafing movement while maintaining
 * current viewing direction.
 *
 * @param g Game structure
 */
void	move_left(t_game *g)
{
	double	move_x;
	double	move_y;

	move_x = -g->player.plane_x * MOVE_SPEED;
	move_y = -g->player.plane_y * MOVE_SPEED;
	safe_move(g, g->player.x + move_x, g->player.y + move_y);
	render_frame(g);
}

/**
 * @brief Strafe player right (perpendicular to current direction)
 *
 * Uses camera plane vector for right strafing movement while maintaining
 * current viewing direction.
 *
 * @param g Game structure
 */
void	move_right(t_game *g)
{
	double	move_x;
	double	move_y;

	move_x = g->player.plane_x * MOVE_SPEED;
	move_y = g->player.plane_y * MOVE_SPEED;
	safe_move(g, g->player.x + move_x, g->player.y + move_y);
	render_frame(g);
}

/**
 * @brief Rotates player view and camera plane
 *
 * Applies rotation matrix to both direction and camera plane vectors
 * to create smooth turning effect. Positive rot_speed turns right,
 * negative turns left.
 *
 * @param g Game structure
 * @param rot_speed Rotation speed/angle in radians
 */
void	rotate_player(t_game *g, double rot_speed)
{
	double old_dir_x = g->player.dir_x;
	g->player.dir_x = old_dir_x * cos(rot_speed) - g->player.dir_y
		* sin(rot_speed);
	g->player.dir_y = old_dir_x * sin(rot_speed) + g->player.dir_y
		* cos(rot_speed);

	double old_plane_x = g->player.plane_x;
	g->player.plane_x = old_plane_x * cos(rot_speed) - g->player.plane_y
		* sin(rot_speed);
	g->player.plane_y = old_plane_x * sin(rot_speed) + g->player.plane_y
		* cos(rot_speed);

	render_frame(g);
}