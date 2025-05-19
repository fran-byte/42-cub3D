/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:39:22 by user              #+#    #+#             */
/*   Updated: 2025/05/19 18:29:10 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_wall(t_game *g, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    // Verificar límites del mapa usando height_map
    if (map_x < 0 || map_y < 0 || map_y >= g->map.height_map ||
        map_x >= (int)ft_strlen(g->map.map[map_y]))
        return (1);

    // Verificar si es una pared
    if (g->map.map[map_y][map_x] == '1')
        return (1);

    return (0);
}

static void safe_move(t_game *g, double new_x, double new_y)
{
    // Movimiento en X
    if (!is_wall(g, new_x, g->player.y))
        g->player.x = new_x;

    // Movimiento en Y
    if (!is_wall(g, g->player.x, new_y))
        g->player.y = new_y;

    // Actualizar también las coordenadas player_x y player_y
    g->player.player_x = g->player.x;
    g->player.player_y = g->player.y;
}

void move_forward(t_game *g)
{
    double move_x = g->player.dir_x * MOVE_SPEED;
    double move_y = g->player.dir_y * MOVE_SPEED;
    safe_move(g, g->player.x + move_x, g->player.y + move_y);
    render_frame(g);
}

void move_backward(t_game *g)
{
    double move_x = -g->player.dir_x * MOVE_SPEED;
    double move_y = -g->player.dir_y * MOVE_SPEED;
    safe_move(g, g->player.x + move_x, g->player.y + move_y);
    render_frame(g);
}

void move_left(t_game *g)
{
    double move_x = -g->player.plane_x * MOVE_SPEED;
    double move_y = -g->player.plane_y * MOVE_SPEED;
    safe_move(g, g->player.x + move_x, g->player.y + move_y);
    render_frame(g);
}

void move_right(t_game *g)
{
    double move_x = g->player.plane_x * MOVE_SPEED;
    double move_y = g->player.plane_y * MOVE_SPEED;
    safe_move(g, g->player.x + move_x, g->player.y + move_y);
    render_frame(g);
}

void rotate_player(t_game *g, double rot_speed)
{
    double old_dir_x = g->player.dir_x;
    g->player.dir_x =
        old_dir_x * cos(rot_speed) - g->player.dir_y * sin(rot_speed);
    g->player.dir_y =
        old_dir_x * sin(rot_speed) + g->player.dir_y * cos(rot_speed);

    double old_plane_x = g->player.plane_x;
    g->player.plane_x =
        old_plane_x * cos(rot_speed) - g->player.plane_y * sin(rot_speed);
    g->player.plane_y =
        old_plane_x * sin(rot_speed) + g->player.plane_y * cos(rot_speed);

    render_frame(g);
}