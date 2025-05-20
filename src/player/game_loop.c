/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:23:34 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:11:37 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Gracefully exits the game and frees all allocated resources.
 *
 * Destroys the MLX window if it exists, frees all game-related memory,
 * and terminates the program with exit code 0 (success).
 *
 * @param game Pointer to the game structure containing MLX pointers and
 * resources.
 * @return Always returns 0 (unused, required for MLX hook compatibility).
 */
int exit_game(t_game *game)
{
    if (game->window)
        mlx_destroy_window(game->mlx, game->window);
    free_function(game);
    exit(0);
    return (0);
}

/**
 * @brief Initializes the main game loop and event hooks.
 *
 * Sets up keyboard and window close event handlers. Verifies MLX initialization
 * before starting the loop. Exits with failure if MLX resources aren't
 * available.
 *
 * @param game Pointer to the game structure containing MLX context and window.
 */
void game_loop(t_game *game)
{
    if (!game->mlx || !game->window)
    {
        report_err(MLX_OR_WINDOW_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }
    mlx_hook(game->window, 2, 1L << 0, key_press, game); // Teclado
    mlx_hook(game->window, 17, 0, exit_game, game);      // Botón cerrar
    mlx_loop(game->mlx);
}
