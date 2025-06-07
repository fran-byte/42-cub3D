/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:22:24 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:22:32 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Updates the player's orientation for texture/sprite rendering
 *
 * Determines the player's cardinal orientation (N, S, E, W) based on the
 * direction vector.
 *
 * @param g Game structure
 */
static void	update_player_orientation(t_game *g)
{
	if (fabs(g->player.dir_x) > fabs(g->player.dir_y))
	{
		if (g->player.dir_x > 0)
			g->player.player_orientation = EAST;
		else
			g->player.player_orientation = WEST;
	}
	else
	{
		if (g->player.dir_y > 0)
			g->player.player_orientation = SOUTH;
		else
			g->player.player_orientation = NORTH;
	}
}

/**
 * @brief Rotates player view and camera plane
 *
 * Applies rotation matrix to both direction and camera plane vectors
 * to create smooth turning effect. Positive angle turns right,
 * negative turns left.
 *
 * @param g Game structure
 * @param angle Rotation angle in radians
 */
void	rotate_view(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = old_dir_x * cos(angle) - g->player.dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);
	g->player.plane_x = old_plane_x * cos(angle) - g->player.plane_y
		* sin(angle);
	g->player.plane_y = old_plane_x * sin(angle) + g->player.plane_y
		* cos(angle);
	update_player_orientation(g);
	render_frame(g);
}
