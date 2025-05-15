/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:34:57 by user              #+#    #+#             */
/*   Updated: 2025/05/14 20:11:24 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        exit_game(game);
    if (keycode == KEY_W)
        move_forward(game);
    if (keycode == KEY_S)
        move_backward(game);
    if (keycode == KEY_A)
        move_left(game);
    if (keycode == KEY_D)
        move_right(game);
    if (keycode == KEY_LEFT)
        rotate_view(game, -MOVE_SPEED);
    if (keycode == KEY_RIGHT)
        rotate_view(game, +MOVE_SPEED);

    if (keycode == KEY_L) // ELIMINAR SOLO DEBUG ***************
        debug_render_test_wall(game, 1);
    if (keycode == KEY_K) // ELIMINAR SOLO DEBUG ***************
        debug_render_test_wall(game, 2);

    printf("Pos: %.2f, %.2f | Dir: %.2f, %.2f\n", game->player.x,
           game->player.y, game->player.dir_x, game->player.dir_y);
    return (0);
}
