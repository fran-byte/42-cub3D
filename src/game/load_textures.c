/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:43:11 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 18:59:28 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Frees allocated resources and exits the program on texture loading
 * error.
 *
 * @param game Pointer to the main game structure that holds allocated
 * resources.
 */
static void free_error(t_game *game)
{
    report_err(TEXTURE_LOADING_ERROR);
    free_function(game);
    exit(EXIT_FAILURE);
}

/**
 * @brief Loads wall textures from XPM files using MiniLibX.
 *
 * This function attempts to load all four wall textures (north, south, west,
 * east) into the game structure using paths previously stored. It also checks
 * if the textures were loaded successfully and have valid dimensions.
 *
 * If any texture fails to load or if the dimensions are incorrect,
 * the program will exit using free_error().
 *
 * @param g Pointer to the main game structure.
 */
void load_textures(t_game *g)
{
    int tex_w[4];
    int tex_h[4];

    g->map.sprites.no =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.north, &tex_w[0], &tex_h[0]);
    if (!g->map.sprites.no)
        free_error(g);

    g->map.sprites.su =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.south, &tex_w[1], &tex_h[1]);
    if (!g->map.sprites.su)
        free_error(g);

    g->map.sprites.we =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.west, &tex_w[2], &tex_h[2]);
    if (!g->map.sprites.we)
        free_error(g);

    g->map.sprites.ea =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.east, &tex_w[3], &tex_h[3]);
    if (!g->map.sprites.ea)
        free_error(g);

    if (!check_texture_sizes(tex_w, tex_h))
        free_error(g);
}
