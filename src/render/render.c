/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:33:15 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 19:05:42 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
    // calculate_raycasting(g, rays);

    // 2. Limpiar imagen anterior
    ft_memset(g->img.addr, 0, SCREEN_HEIGHT * g->img.line_len);

    // 3. Renderizar todas las columnas
    while (x < SCREEN_WIDTH)
    {
        render_wall(g, x, &rays[x]); // game, columna, datos del rayo
        x++;
    }

    // 4. Actualizar ventana
    mlx_put_image_to_window(g->mlx, g->window, g->img.img, 0, 0);
}
