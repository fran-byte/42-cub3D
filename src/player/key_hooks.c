/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:34:57 by user              #+#    #+#             */
/*   Updated: 2025/04/10 23:24:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_game *game)
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

	printf("Pos: %.2f, %.2f | Dir: %.2f, %.2f\n",
		game->player.x, game->player.y,
		game->player.dir_x, game->player.dir_y);
	return (0);
}