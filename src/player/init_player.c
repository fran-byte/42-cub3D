/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:14:02 by user              #+#    #+#             */
/*   Updated: 2025/04/11 09:25:27 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_player(t_game *data)
{
	data->player.x = data->player.player_x;
	data->player.y = data->player.player_y;
	init_player_vectors(data);
}
