/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:19:58 by user              #+#    #+#             */
/*   Updated: 2025/04/11 09:25:26 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void set_north(t_game *p)
{
	p->player.dir_x = 0;
	p->player.dir_y = -1;
	p->player.plane_x = FOV_COEF;
	p->player.plane_y = 0;
}

static void set_south(t_game *p)
{
	p->player.dir_x = 0;
	p->player.dir_y = 1;
	p->player.plane_x = -FOV_COEF;
	p->player.plane_y = 0;
}

static void set_east(t_game *p)
{
	p->player.dir_x = 1;
	p->player.dir_y = 0;
	p->player.plane_x = 0;
	p->player.plane_y = FOV_COEF;
}

static void set_west(t_game *p)
{
	p->player.dir_x = -1;
	p->player.dir_y = 0;
	p->player.plane_x = 0;
	p->player.plane_y = -FOV_COEF;
}

void init_player_vectors(t_game *p)
{
	if (p->player.player_orinetation == NORTH)
		set_north(p);
	else if (p->player.player_orinetation == SOUTH)
		set_south(p);
	else if (p->player.player_orinetation == EAST)
		set_east(p);
	else if (p->player.player_orinetation == WEST)
		set_west(p);
}
