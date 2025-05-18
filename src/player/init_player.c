/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:14:02 by user              #+#    #+#             */
/*   Updated: 2025/05/15 19:27:41 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_player(t_game *game)
{
    game->player.x = game->player.player_x;
    game->player.y = game->player.player_y;
    init_player_vectors(game);
}
