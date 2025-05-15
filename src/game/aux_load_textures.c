/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_load_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:47:40 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 14:18:58 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool check_texture_sizes(t_game *g)
{
    int widths[4];
    int heights[4];
    int i;

    i = 1;
    mlx_get_data_addr(g->map.sprites.no, &g->img.bpp, &widths[0],
                      &g->img.endian);
    mlx_get_data_addr(g->map.sprites.su, &g->img.bpp, &widths[1],
                      &g->img.endian);
    mlx_get_data_addr(g->map.sprites.ea, &g->img.bpp, &widths[2],
                      &g->img.endian);
    mlx_get_data_addr(g->map.sprites.we, &g->img.bpp, &widths[3],
                      &g->img.endian);
    while (i < 4)
    {
        if (widths[i] != widths[0] || heights[i] != heights[0])
            return false;
        i++;
    }
    return (true);
}

void clean_exit(t_game *g, int exit_code)
{
    if (g->map.sprites.no)
        mlx_destroy_image(g->mlx, g->map.sprites.no);
    if (g->map.sprites.su)
        mlx_destroy_image(g->mlx, g->map.sprites.su);
    if (g->map.sprites.ea)
        mlx_destroy_image(g->mlx, g->map.sprites.ea);
    if (g->map.sprites.we)
        mlx_destroy_image(g->mlx, g->map.sprites.we);
    free_function(g);
    exit(exit_code);
}