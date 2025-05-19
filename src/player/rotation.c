/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:22:24 by user              #+#    #+#             */
/*   Updated: 2025/05/19 18:32:09 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void update_player_orientation(t_game *g)
{
    // Determinamos la orientación principal basada en el vector dirección
    if (fabs(g->player.dir_x) > fabs(g->player.dir_y))
    {
        if (g->player.dir_x > 0)
            g->player.player_orientation = EAST;
        else
            g->player.player_orientation = WEST;
    }
    else
    {
        if (g->player.dir_y > 0)
            g->player.player_orientation = SOUTH;
        else
            g->player.player_orientation = NORTH;
    }
}

void rotate_view(t_game *g, double angle)
{
    double old_dir_x;
    double old_plane_x;

    // Bloqueamos la rotación si el juego está pausado o en estado especial
    // if (g->game_state != GAME_RUNNING)
    //     return;

    // Guardamos los valores antiguos
    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;

    // Rotación del vector dirección (player)
    g->player.dir_x = old_dir_x * cos(angle) - g->player.dir_y * sin(angle);
    g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);

    // Rotación del plano de la cámara (para el efecto FOV)
    g->player.plane_x =
        old_plane_x * cos(angle) - g->player.plane_y * sin(angle);
    g->player.plane_y =
        old_plane_x * sin(angle) + g->player.plane_y * cos(angle);

    // Actualizamos la orientación del jugador para texturas/sprite
    update_player_orientation(g);

    // Forzamos un nuevo renderizado
    render_frame(g);
}
