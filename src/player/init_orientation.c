/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:19:58 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:14:42 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Sets player direction vectors for NORTH orientation
 *
 * Initializes the player's direction vector to point north (negative Y axis)
 * and sets the camera plane perpendicular to the right (positive X axis).
 *
 * @param p Pointer to game structure containing player data
 */
static void	set_north(t_game *p)
{
	p->player.dir_x = 0;
	p->player.dir_y = -1;
	p->player.plane_x = FOV_COEF;
	p->player.plane_y = 0;
}

/**
 * @brief Sets player direction vectors for SOUTH orientation
 *
 * Initializes the player's direction vector to point south (positive Y axis)
 * and sets the camera plane perpendicular to the left (negative X axis).
 *
 * @param p Pointer to game structure containing player data
 */
static void	set_south(t_game *p)
{
	p->player.dir_x = 0;
	p->player.dir_y = 1;
	p->player.plane_x = -FOV_COEF;
	p->player.plane_y = 0;
}

/**
 * @brief Sets player direction vectors for EAST orientation
 *
 * Initializes the player's direction vector to point east (positive X axis)
 * and sets the camera plane perpendicular upwards (positive Y axis).
 *
 * @param p Pointer to game structure containing player data
 */
static void	set_east(t_game *p)
{
	p->player.dir_x = 1;
	p->player.dir_y = 0;
	p->player.plane_x = 0;
	p->player.plane_y = FOV_COEF;
}

/**
 * @brief Sets player direction vectors for WEST orientation
 *
 * Initializes the player's direction vector to point west (negative X axis)
 * and sets the camera plane perpendicular downwards (negative Y axis).
 *
 * @param p Pointer to game structure containing player data
 */
static void	set_west(t_game *p)
{
	p->player.dir_x = -1;
	p->player.dir_y = 0;
	p->player.plane_x = 0;
	p->player.plane_y = -FOV_COEF;
}

/**
 * @brief Initializes player direction and camera plane vectors
 *
 * Configures the player's initial direction and camera plane based on
 * their starting orientation (NORTH, SOUTH, EAST, or WEST) which was
 * determined during map parsing.
 *
 * @param p Pointer to game structure containing player data
 */
void	init_player_vectors(t_game *p)
{
	if (p->player.player_orientation == NORTH)
		set_north(p);
	else if (p->player.player_orientation == SOUTH)
		set_south(p);
	else if (p->player.player_orientation == EAST)
		set_east(p);
	else if (p->player.player_orientation == WEST)
		set_west(p);
}