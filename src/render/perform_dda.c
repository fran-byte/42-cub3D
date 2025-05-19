/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:42:17 by user              #+#    #+#             */
/*   Updated: 2025/05/18 18:21:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void perform_dda(t_game *g, t_ray_vars *v)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (v->side_dist_x < v->side_dist_y)
		{
			v->side_dist_x += v->delta_dist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->side_dist_y += v->delta_dist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (g->map.map[v->map_y][v->map_x] == '1')
			hit = 1;
	}
}
