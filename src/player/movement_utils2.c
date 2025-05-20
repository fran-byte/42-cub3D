/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:00:35 by frromero          #+#    #+#             */
/*   Updated: 2025/05/20 21:07:10 by frromero         ###   ########.fr       */
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
int	is_wall(t_game *g, double x, double y)
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
void	safe_move(t_game *g, double new_x, double new_y)
{
	if (!is_wall(g, new_x, g->player.y))
		g->player.x = new_x;
	if (!is_wall(g, g->player.x, new_y))
		g->player.y = new_y;
	g->player.player_x = g->player.x;
	g->player.player_y = g->player.y;
}
