/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:27:59 by frromero          #+#    #+#             */
/*   Updated: 2025/05/15 11:37:58 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Dibuja una línea vertical en la columna 'x' desde 'start_y' hasta 'end_y' con
 * un color. Usaremos esto para simular paredes.
 */
static void draw_vert_line(t_game *g, int x, int start_y, int end_y, int color)
{
    int y;

    y = start_y;
    while (y < end_y)
    {
        mlx_pixel_put(g->mlx, g->window, x, y, color);
        y++;
    }
}

/*
 * Simula una "pared" simple para pruebas:
 * - Columna central (x = SCREEN_WIDTH/2)
 * - Altura fija (mitad de la pantalla)
 * - Color rojo
 */
void debug_render_test_wall(t_game *g, int i)
{
    int color = 0x000000;

    int wall_x;
    int wall_height;
    int draw_start;
    int draw_end;
    int z = 0;

    wall_x = SCREEN_WIDTH / 2;                      // Columna central
    wall_height = SCREEN_HEIGHT / 3;                // Altura fija
    draw_start = (SCREEN_HEIGHT - wall_height) / 2; // Centrar verticalmente
    draw_end = draw_start + wall_height;
    if (i == 1)
        color = 0xFF0000; // Color Rojo
    else if (i == 2)
        color = 0x000000; // Color Negro

    while (z < 100)
    {
        draw_vert_line(g, wall_x + z, draw_start + z, draw_end + z, color);
        z = z + 10;
    }
}
