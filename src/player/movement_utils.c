/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:39:22 by user              #+#    #+#             */
/*   Updated: 2025/04/10 16:42:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


static int	is_wall(t_game *g, double x, double y)
{
	if (g->map.map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	move_forward(t_game *g)
{
	double nx = g->player.x + g->player.dir_x * MOVE_SPEED;
	double ny = g->player.y + g->player.dir_y * MOVE_SPEED;

	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
}

void	move_backward(t_game *g)
{
	double nx = g->player.x - g->player.dir_x * MOVE_SPEED;
	double ny = g->player.y - g->player.dir_y * MOVE_SPEED;

	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
}

void	move_left(t_game *g)
{
	double nx = g->player.x - g->player.plane_x * MOVE_SPEED;
	double ny = g->player.y - g->player.plane_y * MOVE_SPEED;

	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
}

void	move_right(t_game *g)
{
	double nx = g->player.x + g->player.plane_x * MOVE_SPEED;
	double ny = g->player.y + g->player.plane_y * MOVE_SPEED;

	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
}
