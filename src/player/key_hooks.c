/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:34:57 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:16:38 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Handles keyboard input events for player control
 *
 * Processes key presses and triggers corresponding game actions:
 * - ESC: Exits game cleanly
 * - WASD: Player movement (forward/backward/strafe)
 * - Arrow keys: Camera rotation
 *
 * @param keycode The key that was pressed (defined in key macros)
 * @param game Pointer to main game structure containing player and state
 * @return int Always returns 0 (MLX hook convention)
 */
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
    return (0);
}
