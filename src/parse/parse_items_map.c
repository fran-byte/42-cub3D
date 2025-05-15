/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:08:51 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:23:41 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Sets the player's starting position and orientation.
 *
 * Stores the player's coordinates and facing direction based on the character
 * in the map (N, S, E, W), and increments the player counter.
 *
 * @param game Pointer to the main game structure.
 * @param x Pointer to the current x-coordinate in the map.
 * @param y Pointer to the current y-coordinate in the map.
 * @param player Pointer to the number of player positions found.
 */
static void add_orientation(t_game *game, int *x, int *y, int *player)
{
    game->player.player_x = *x;
    game->player.player_y = *y;
    if (game->map.map[*y][*x] == 'W')
        game->player.player_orientation = WEST;
    else if (game->map.map[*y][*x] == 'E')
        game->player.player_orientation = EAST;
    else if (game->map.map[*y][*x] == 'N')
        game->player.player_orientation = NORTH;
    else if (game->map.map[*y][*x] == 'S')
        game->player.player_orientation = SOUTH;
    *player += 1;
}

/**
 * @brief Handles invalid item errors in the map.
 *
 * Frees allocated memory, shows an error message, and exits the program.
 *
 * @param game Pointer to the main game structure.
 */
static void error_items(t_game *game)
{
    report_err(MAP_ITENS_ERR);
    free_function(game);
    exit(EXIT_FAILURE);
}

/**
 * @brief Parses and validates each character in the map.
 *
 * Checks for valid map characters (0, 1, player orientations, etc.),
 * calls error handler for invalid ones, and stores player orientation.
 *
 * @param game Pointer to the main game structure.
 * @param player Pointer to the number of player positions found.
 */
static void count_and_store_items(t_game *game, int *player)
{
    int x;
    int y;
    int line_len;

    y = 0;
    while (y < game->map.height_map)
    {
        line_len = ft_strlen(game->map.map[y]);
        x = 0;
        while (x < line_len)
        {
            if (game->map.map[y][x] != 'W' && game->map.map[y][x] != 'E' &&
                game->map.map[y][x] != 'S' && game->map.map[y][x] != 'N' &&
                game->map.map[y][x] != '0' && game->map.map[y][x] != '1' &&
                game->map.map[y][x] != ' ' && game->map.map[y][x] != '\t')
                error_items(game);
            else if (game->map.map[y][x] == 'W' || game->map.map[y][x] == 'E' ||
                     game->map.map[y][x] == 'S' || game->map.map[y][x] == 'N')
                add_orientation(game, &x, &y, player);
            x++;
        }
        y++;
    }
}

/**
 * @brief Main function to parse map items and validate player start.
 *
 * Ensures the map contains exactly one player start position.
 * Exits the program if invalid items or multiple players are found.
 *
 * @param game Pointer to the main game structure.
 */
void parse_items_map(t_game *game)
{
    int player;
    player = 0;

    count_and_store_items(game, &player);
    if (player != 1)
    {
        report_err(MAP_ITENS_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }
}
