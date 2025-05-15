/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:43:11 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:20 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void free_error(t_game *game)
{
    report_err(TEXTURE_LOADING_ERROR);
    free_function(game);
    exit(EXIT_FAILURE);
}

void load_textures(t_game *g)
{
    int tex_w;
    int tex_h; // Para almacenar ancho/alto de texturas

    g->map.sprites.no =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.north, &tex_w, &tex_h);
    if (!g->map.sprites.no)
        free_error(g);
    g->map.sprites.su =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.south, &tex_w, &tex_h);
    if (!g->map.sprites.su)
        free_error(g);
    g->map.sprites.we =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.west, &tex_w, &tex_h);
    if (!g->map.sprites.no)
        free_error(g);
    g->map.sprites.ea =
        mlx_xpm_file_to_image(g->mlx, g->map.paths.east, &tex_w, &tex_h);
    if (!g->map.sprites.su)
        free_error(g);
}