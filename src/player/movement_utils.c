/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:39:22 by user              #+#    #+#             */
/*   Updated: 2025/05/20 21:10:04 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	g->player.dir_x = old_dir_x * cos(rot_speed) - g->player.dir_y
		* sin(rot_speed);
	g->player.dir_y = old_dir_x * sin(rot_speed) + g->player.dir_y
		* cos(rot_speed);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = old_plane_x * cos(rot_speed) - g->player.plane_y
		* sin(rot_speed);
	g->player.plane_y = old_plane_x * sin(rot_speed) + g->player.plane_y
		* cos(rot_speed);
	render_frame(g);
}
