/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:54:44 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 13:50:09 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Obtiene los píxeles de la textura correspondiente a la dirección de la pared.
 * Devuelve un array de enteros (colores) y actualiza el ancho de la textura.
 */
static int *get_texture_pixels(t_game *g, t_orientation wall_dir,
                               int *tex_width)
{
    void *texture;

    // 1. Seleccionar textura según dirección
    if (wall_dir == NORTH)
        texture = g->map.sprites.no;
    else if (wall_dir == SOUTH)
        texture = g->map.sprites.su;
    else if (wall_dir == EAST)
        texture = g->map.sprites.ea;
    else
        texture = g->map.sprites.we;

    // 2. Obtener datos de la textura
    int tex_height;
    int *tex_data = (int *)mlx_get_data_addr(texture, &g->img.bpp, tex_width,
                                             &g->img.endian);
    *tex_width /= 4; // Ajustar para 32 bits (4 bytes por píxel)

    return tex_data;
}

/*Renderiza una columna de pared con textura.*
    -x : Posición horizontal en pantalla.*
    -ray : Datos del rayo calculados por el raycasting.*/
void render_wall(t_game *g, int x, t_ray_info *ray)
{
    t_wall_info w;

    w.x = x;
    w.texture = get_texture_pixels(g, ray->wall_dir, &w.tex_width);
    w.tex_x = ray->tex_x;
    w.step = (double)w.tex_width / ray->wall_height;
    w.tex_pos =
        (ray->draw_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * w.step;
    w.y = ray->draw_start;

    while (w.y < ray->draw_end)
    {
        int tex_y = (int)w.tex_pos & (w.tex_width - 1);
        w.tex_pos += w.step;

        int color = w.texture[tex_y * w.tex_width + w.tex_x];
        int pixel = (w.y * g->img.line_len) + (w.x * (g->img.bpp / 8));
        *(int *)(g->img.addr + pixel) = color;

        w.y++;
    }
}
