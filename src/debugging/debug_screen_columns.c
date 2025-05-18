/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_screen_columns.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:13:33 by user              #+#    #+#             */
/*   Updated: 2025/05/18 19:20:04 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void debug_print_column(t_ray_info rays[])
{
	int x = 0;
	const char *dirs[] = { "EAST", "WEST", "NORTH", "SOUTH" };

	while (x < SCREEN_WIDTH)
	{
		printf(
			"[x=%3d] dir=%s | dist=%.2f | height=%3d | tex_x=%2d | draw=(%3d→%3d)\n",
			x,
			dirs[rays[x].wall_dir],
			rays[x].distance,
			rays[x].wall_height,
			rays[x].tex_x,
			rays[x].draw_start,
			rays[x].draw_end
		);
		x++;
	}
}