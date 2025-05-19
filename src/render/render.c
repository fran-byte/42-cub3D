/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:33:15 by frromero          #+#    #+#             */
/*   Updated: 2025/05/19 20:17:49 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void render_floor(t_game *g, int y_start, int color)
{
    int x;
    int y = y_start;

    while (y < SCREEN_HEIGHT)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            int pixel = (y * g->img.line_len) + (x * (g->img.bpp / 8));
            *(int *)(g->img.addr + pixel) = color;
            x++;
        }
        y++;
    }
}

void render_ceiling(t_game *g, int y_end, int color)
{
    int x;
    int y = 0;

    while (y < y_end)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            int pixel = (y * g->img.line_len) + (x * (g->img.bpp / 8));
            *(int *)(g->img.addr + pixel) = color;
            x++;
        }
        y++;
    }
}

/**
 * @brief Renders a complete frame by casting rays and drawing walls.
 *
 * This function clears the previous frame, performs raycasting to determine
 * wall positions and textures, renders all vertical wall slices, and updates
 * the window with the new image.
 *
 * @param g Pointer to the main game structure containing all rendering info.
 */
void render_frame(t_game *g)
{
    int x;

    x = 0;
    t_ray_info rays[SCREEN_WIDTH];

    // 1. Calcular raycasting
    calculate_raycasting(g, rays);
    // debug_print_column(rays);
    //  2. Renderizar techo (usando color del .cub)
    render_ceiling(g, SCREEN_HEIGHT / 2, g->map.ceiling_color);

    // 3. Renderizar suelo (usando color del .cub)
    render_floor(g, SCREEN_HEIGHT / 2, g->map.floor_color);
    // 2. Limpiar imagen anterior
    // ft_memset(g->img.addr, 0, SCREEN_HEIGHT * g->img.line_len);

    // 3. Renderizar todas las columnas
    while (x < SCREEN_WIDTH)
    {
        render_wall(g, x, &rays[x]); // game, columna, datos del rayo
        x++;
    }

    // 4. Actualizar ventana
    mlx_put_image_to_window(g->mlx, g->window, g->img.img, 0, 0);
}
