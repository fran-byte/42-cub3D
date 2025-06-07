/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:23:34 by user              #+#    #+#             */
/*   Updated: 2025/06/07 18:40:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Handles the intro animation loop by displaying frames sequentially.
 *
 * This function is called on every iteration of the main MLX loop via
 * mlx_loop_hook. It checks whether the intro is active, displays the current
 * frame, increments a tick counter, and advances to the next frame after a 
 * fixed number of ticks. The number 120 defines how many loop cycles each 
 * frame should remain visible before switching to the next one.
 *
 * @param g Pointer to the game structure containing intro frame data.
 * @return Always returns 0 (required by MLX loop hook signature).
 */
int	intro_loop(t_game *g)
{
	if (!g->intro.active)
		return (0);
	mlx_put_image_to_window(g->mlx, g->window,
		g->intro.frames[g->intro.current_frame], 0, 0);
	g->intro.ticks++;
	if (g->intro.ticks >= 120)
	{
		g->intro.current_frame = (g->intro.current_frame + 1)
			% INTRO_FRAME_COUNT;
		g->intro.ticks = 0;
	}
	return (0);
}

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
int	exit_game(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	free_function(game);
	exit(0);
	return (0);
}

/**
 * @brief Starts the main game loop.
 *
 * Checks if the MLX context and window are properly initialized.
 * Sets up event hooks for keyboard input and window close events,
 * then enters the main rendering loop using mlx_loop.
 *
 * @param game Pointer to the main game structure.
 */
void	game_loop(t_game *game)
{
	if (!game->mlx || !game->window)
	{
		report_err(MLX_OR_WINDOW_ERR);
		free_function(game);
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(game->mlx, intro_loop, game);
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 17, 0, exit_game, game);
	mlx_loop(game->mlx);
}
