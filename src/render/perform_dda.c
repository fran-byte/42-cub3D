/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:42:17 by user              #+#    #+#             */
/*   Updated: 2025/05/20 20:24:36 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Executes the DDA (Digital Differential Analyzer) algorithm
 *
 * Steps through the grid map one square at a time to detect the first wall hit
 * by the ray, setting which side (X or Y) was hit.
 *
 * @param g Game structure
 * @param v Raycasting variables (updated during the process)
 */
void	perform_dda(t_game *g, t_ray_vars *v)
{
	int	hit;

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
