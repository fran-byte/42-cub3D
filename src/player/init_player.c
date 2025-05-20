/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:14:02 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:15:36 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initializes the player's position and direction vectors
 *
 * Sets the player's starting position from the map data and initializes
 * their direction and camera plane vectors based on starting orientation.
 * This function serves as the main initialization point for all player-related
 * movement and rendering parameters.
 *
 * @param game Pointer to the main game structure containing player data
 */
void init_player(t_game *game)
{
    game->player.x = game->player.player_x;
    game->player.y = game->player.player_y;
    init_player_vectors(game);
}
