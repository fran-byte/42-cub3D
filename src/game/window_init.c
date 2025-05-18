/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:34:10 by user              #+#    #+#             */
/*   Updated: 2025/05/15 18:44:59 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initializes the MLX window and game image buffer.
 *
 * Sets up the MLX context, creates the game window and image,
 * and loads all required textures. Exits on failure.
 *
 * @param game Pointer to the game structure.
 * @param width Width of the game window.
 * @param height Height of the game window.
 */
void window_init(t_game *game, int width, int height)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        report_err(MLX_INIT_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    game->window = mlx_new_window(game->mlx, width, height, "Cub3D");
    if (!game->window)
    {
        mlx_destroy_display(game->mlx);
        report_err(MLX_NEW_WINDOW_ERR);
        free_function(game);
        exit(EXIT_FAILURE);
    }

    game->img.img = mlx_new_image(game->mlx, width,
                                  height); // AÑADIDA
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, // AÑADIDA
                                       &game->img.line_len, &game->img.endian);
    load_textures(game); // AÑADIDA *********************
}
