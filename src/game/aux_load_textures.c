/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_load_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:47:40 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 15:24:59 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool check_texture_sizes(int *w, int *h)
{
    for (int i = 1; i < 4; i++)
    {
        if (w[i] != w[0] || h[i] != h[0])
            return false;
    }
    return true;
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