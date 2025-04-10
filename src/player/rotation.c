/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:22:24 by user              #+#    #+#             */
/*   Updated: 2025/04/10 23:22:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void rotate_view(t_game *g, double angle)
{
	double old_dir_x = g->player.dir_x;
	double old_plane_x = g->player.plane_x;

	// Rotamos el vector de dirección
	g->player.dir_x = g->player.dir_x * cos(angle) - g->player.dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);

	// Rotamos el vector del plano
	g->player.plane_x = g->player.plane_x * cos(angle) - g->player.plane_y * sin(angle);
	g->player.plane_y = old_plane_x * sin(angle) + g->player.plane_y * cos(angle);
}
